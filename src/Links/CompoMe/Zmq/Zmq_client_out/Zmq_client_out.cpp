#include "Links/CompoMe/Zmq/Zmq_client_out/Zmq_client_out.hpp"
#include "CompoMe/Log.hpp"
#include "Interfaces/Interface.hpp"
#include <iostream>
#include <string.h>
#include <zmq.h>

namespace CompoMe {

namespace Zmq {

Zmq_client_out::Zmq_client_out() : CompoMe::Link(), fss(*this), rsr(*this) {
  a_context = zmq_ctx_new();
  a_requester = zmq_socket(a_context, ZMQ_REQ);
}

Zmq_client_out::~Zmq_client_out() {
  zmq_close(this->a_requester);
  zmq_ctx_term(this->a_context);
}

void Zmq_client_out::step() { Link::step(); }

void Zmq_client_out::connect() {
  Link::connect();
  auto r = zmq_connect(this->a_requester, this->addr.str.c_str());
  if (r != 0) {
    C_ERROR_TAG("zmq,client,connect", "Fail of connection at ", this->addr,
                " with (", errno, ") ", strerror(errno));
  }

  this->f = this->a_re->fake_stream_it(fss, rsr);
  if (this->f == NULL) {
    C_ERROR_TAG(
        "zmq,client,fake",
        "The build of fake_stream fail. it will no be possible to call it.");
  }
}

void Zmq_client_out::disconnect() {
  Link::disconnect();
  if (this->f != nullptr) {
    delete this->f;
  }
}

CompoMe::String Zmq_client_out::get_addr() const { return this->addr; }

void Zmq_client_out::set_addr(const CompoMe::String p_addr) {
  this->addr = p_addr;
}
CompoMe::String Zmq_client_out::get_to_interface() const {
  return this->to_interface;
}

void Zmq_client_out::set_to_interface(const CompoMe::String p_to_interface) {
  this->to_interface = p_to_interface;
}
CompoMe::String Zmq_client_out::get_to_component() const {
  return this->to_component;
}

void Zmq_client_out::set_to_component(const CompoMe::String p_to_component) {
  this->to_component = p_to_component;
}

// stream
Return_string_stream_recv::Return_string_stream_recv(Zmq_client_out &p_l)
    : CompoMe::Return_stream_recv(), a_l(p_l) {}

void Return_string_stream_recv::pull() {
  char l_buffer[1024 + 2];
  auto e = zmq_recv(this->a_l.get_sock(), l_buffer, 1024, 0);

  l_buffer[e] = ' ';
  l_buffer[e + 1] = '\0';
  C_DEBUG_TAG("zmq,client,recv", "answer: ", l_buffer);
  std::string str(l_buffer);
  this->a_ss.str(str);
}

void Return_string_stream_recv::end() { this->a_ss.str(""); }

Function_string_stream_send::Function_string_stream_send(Zmq_client_out &p_l)
    : a_l(p_l) {}
void Function_string_stream_send::start() {
  this->a_ss.str("");
  if (this->a_l.get_to_component().str != "") {
    this->a_ss << this->a_l.get_to_component().str << ".";
  }

  if (this->a_l.get_to_interface().str != "") {
    this->a_ss << this->a_l.get_to_interface().str << ".";
  }
}

void Function_string_stream_send::send() {
  C_DEBUG_TAG("zmq,client,send", "call: ", this->a_ss.str());
  zmq_send(this->a_l.get_sock(), this->a_ss.str().c_str(),
           this->a_ss.str().size(), 0);
}

} // namespace Zmq

} // namespace CompoMe
