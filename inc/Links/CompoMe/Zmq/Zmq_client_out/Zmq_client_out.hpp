#pragma once

#include "Links/Link.hpp"

namespace CompoMe {
class Function_stream;
class Return_stream;
class Interface;
} // namespace CompoMe

#include "Data/CompoMe_Zmq.hpp"

namespace CompoMe {

namespace Zmq {
class Zmq_client_out;

class Function_string_stream_send : public CompoMe::Function_stream_send {
private:
  std::stringstream a_ss;
  Zmq_client_out &a_l;

public:
  Function_string_stream_send(Zmq_client_out &p_l);
  void start() final;
  void send() final;
  std::ostream &get_so() override { return this->a_ss; }
};

class Return_string_stream_recv : public CompoMe::Return_stream_recv {
private:
  std::stringstream a_ss;
  Zmq_client_out &a_l;
public:
  Return_string_stream_recv(Zmq_client_out &p_l);
  void pull() final;
  void end() final;
  std::istream &get_si() override { return this->a_ss; }
};

class Zmq_client_out : public CompoMe::Link, public CompoMe::Link_out {
public:
  Zmq_client_out();
  virtual ~Zmq_client_out();

  void step() override;
  void connect() override;
  void disconnect() override;

  // Get and set /////////////////////////////////////////////////////////////

  virtual CompoMe::String get_addr() const;
  virtual void set_addr(const CompoMe::String addr);

  virtual CompoMe::String get_to_interface() const;
  virtual void set_to_interface(const CompoMe::String to_interface);

  virtual CompoMe::String get_to_component() const;
  virtual void set_to_component(const CompoMe::String to_component);

public:
  // Function
  // ///////////////////////////////////////////////////////////////////
  void *get_sock() { return this->a_requester; }

private:
  // DATA ////////////////////////////////////////////////////////////////////
  void *a_context;
  void *a_requester;

  CompoMe::Fake_stream *f;
  Function_string_stream_send fss;
  Return_string_stream_recv rsr;

  CompoMe::String addr;

  CompoMe::String to_interface;

  CompoMe::String to_component;
};

} // namespace Zmq

} // namespace CompoMe
