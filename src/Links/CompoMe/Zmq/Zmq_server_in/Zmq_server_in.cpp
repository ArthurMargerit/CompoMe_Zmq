#include "Links/CompoMe/Zmq/Zmq_server_in/Zmq_server_in.hpp"
#include "CompoMe/Log.hpp"
#include "CompoMe/Tools/Call.hpp"
#include "Interfaces/Interface.hpp"
#include <assert.h>
#include <cassert>
#include <zmq.h>

namespace CompoMe {

namespace Zmq {
#define SIZE_BUFFER (1024 * 4)

Zmq_server_in::Zmq_server_in() : CompoMe::Link() {
  this->a_context = zmq_ctx_new();
  this->a_responder = zmq_socket(this->a_context, ZMQ_REP);
}

Zmq_server_in::~Zmq_server_in() {
  zmq_close(this->a_responder);
  zmq_ctx_term(this->a_context);
}

void Zmq_server_in::step() {
  Link::step();
  char buffer[SIZE_BUFFER];
  auto m = zmq_recv(this->a_responder, buffer, SIZE_BUFFER, ZMQ_NOBLOCK);

  // no message
  if (m == -1 && errno == EAGAIN) {
    return;
  }

  buffer[m] = '\0';
  C_DEBUG_TAG("zmq,server,in", "call :", buffer);
  auto l_res =
      CompoMe::Tools::call(&this->get_caller_stream(), std::string(buffer));

  C_DEBUG_TAG("zmq,server,in", "answer : ", l_res.first,
              " return: ", l_res.second.c_str());
  zmq_send(this->a_responder, l_res.second.c_str(), l_res.second.length(), 0);
}

void Zmq_server_in::connect() {
  Link::connect();
  C_DEBUG_TAG("zmq,server,in", "connection bind at ", this->bind_addr);
  int rc = zmq_bind(this->a_responder, this->bind_addr.str.c_str());
  assert(rc == 0);
}

void Zmq_server_in::disconnect() {
  Link::disconnect();
  C_DEBUG_TAG("zmq,server,in", "disconnection");
  zmq_unbind(this->a_responder, this->bind_addr.str.c_str());
}

// Get and set /////////////////////////////////////////////////////////////

CompoMe::String Zmq_server_in::get_bind_addr() const { return this->bind_addr; }

void Zmq_server_in::set_bind_addr(const CompoMe::String p_bind_addr) {
  this->bind_addr = p_bind_addr;
}

} // namespace Zmq

} // namespace CompoMe
