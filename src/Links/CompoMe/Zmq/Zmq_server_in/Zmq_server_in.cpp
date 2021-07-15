#include "Links/CompoMe/Zmq/Zmq_server_in/Zmq_server_in.hpp"
#include "Interfaces/Interface.hpp"
#include "CompoMe/Log.hpp"
#include "CompoMe/Tools/Call.hpp"
#include <zmq.h>

namespace CompoMe {

namespace Zmq {
#define SIZE_BUFFER (1024 * 4)

Zmq_server_in::Zmq_server_in() : CompoMe::Link(), main(), many() {
  this->main.set_link(*this);
  this->many.set_link(*this);

  this->a_context = zmq_ctx_new();
  this->a_responder = zmq_socket(this->a_context, ZMQ_REP);
}

Zmq_server_in::~Zmq_server_in() {
  zmq_close(this->a_responder);
  zmq_ctx_term(this->a_context);
}

void Zmq_server_in::step() {
  Link::step();
  char buffer[SIZE_BUFFER + 2];
  auto m = zmq_recv(this->a_responder, buffer, SIZE_BUFFER, ZMQ_NOBLOCK);

  // no message
  if (m == -1 && errno == EAGAIN) {
    return;
  }

  buffer[m] = '\0';
  C_DEBUG_TAG("zmq,server,in", "call :", buffer);
  auto l_res =
      CompoMe::Tools::call(this->get_main().get_interface().get_caller_stream(),
                           std::string(buffer));

  C_DEBUG_TAG("zmq,server,in", "answer : ", l_res.first,
              " return: ", l_res.second.c_str());
  zmq_send(this->a_responder, l_res.second.c_str(), l_res.second.length(), 0);
}

void Zmq_server_in::main_connect() {
  Link::main_connect();
  C_DEBUG_TAG("zmq,server,in", "connection bind at ", this->bind_addr);
  int rc = zmq_bind(this->a_responder, this->bind_addr.str.c_str());
  C_ERROR_TAG("zmq,server,in", "bind failled with answer ", rc);
}

void Zmq_server_in::main_disconnect() {
  Link::main_disconnect();
  C_DEBUG_TAG("zmq,server,in", "disconnection");
  zmq_unbind(this->a_responder, this->bind_addr.str.c_str());
}

// one connect
void Zmq_server_in::one_connect(CompoMe::Require_helper &p_r,
                                CompoMe::String p_key) {}

void Zmq_server_in::one_connect(CompoMe::Interface &p_i,
                                CompoMe::String p_key) {}

// one disconnect
void Zmq_server_in::one_disconnect(CompoMe::Require_helper &p_r,
                                   CompoMe::String p_key) {}

void Zmq_server_in::one_disconnect(CompoMe::Interface &p_i,
                                   CompoMe::String p_key) {}

} // namespace Zmq

} // namespace CompoMe
