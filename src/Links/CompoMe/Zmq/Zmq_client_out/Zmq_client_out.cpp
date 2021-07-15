#include "Links/CompoMe/Zmq/Zmq_client_out/Zmq_client_out.hpp"
#include "CompoMe/Log.hpp"
#include "Interfaces/Interface.hpp"
#include <zmq.h>


namespace CompoMe {

namespace Zmq {

Zmq_client_out::Zmq_client_out() : CompoMe::Link(), main(), many() {
  C_INFO_TAG("zmq,client", "Creation of Zmq client");

  this->main.set_link(*this);
  this->many.set_link(*this);

  this->a_context = zmq_ctx_new();
  this->a_requester = zmq_socket(a_context, ZMQ_REQ);
}

Zmq_client_out::~Zmq_client_out() {
  C_INFO_TAG("zmq,client", "destruction of Zmq client");
  zmq_close(this->a_requester);
  zmq_ctx_term(this->a_context);
}

void Zmq_client_out::step() { Link::step(); }

  void Zmq_client_out::main_connect() {
    C_INFO_TAG("zmq,client", "Connection ", this->get_addr());
    Link::main_connect();

    auto r = zmq_connect(this->a_requester, this->addr.str.c_str());
    if (r != 0) {
      C_ERROR_TAG("zmq,client,connect", "Fail of connection at ", this->addr,
                  " with (", errno, ") ", strerror(errno));
    }
 }

void Zmq_client_out::main_disconnect() { Link::main_disconnect(); }

// one connect
void Zmq_client_out::one_connect(CompoMe::Require_helper &p_r,
                                 CompoMe::String p_key) {

  auto &nc = this->fake_many[p_key];

  nc.fss.set_func_send([this, p_key](CompoMe::String_d &d) {
    C_DEBUG_TAG("zmq,client,recv", "ask: ", d);
    zmq_send(this->a_requester, d.str.c_str(),
             d.str.size(), 0);

    return true;
  });

  nc.rss.set_func_recv([this](CompoMe::String_d &d) {
    char l_buffer[1024 + 2];
    auto e = zmq_recv(this->a_requester, l_buffer, 1024, 0);
    l_buffer[e] = ' ';
    l_buffer[e + 1] = '\0';

    C_DEBUG_TAG("zmq,client,recv", "answer: ", l_buffer);

    std::string str(l_buffer);
    d = str;

    return true;
  });

  nc.f = p_r.fake_stream_it(nc.fss, nc.rss);
}

void Zmq_client_out::one_connect(CompoMe::Interface &p_i,
                                 CompoMe::String p_key) {}

// one disconnect
void Zmq_client_out::one_disconnect(CompoMe::Require_helper &p_r,
                                    CompoMe::String p_key) {}

void Zmq_client_out::one_disconnect(CompoMe::Interface &p_i,
                                    CompoMe::String p_key) {}

} // namespace Zmq

} // namespace CompoMe
