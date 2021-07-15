#pragma once

#include "Data/CompoMe_Zmq.hpp"

#include "Links/Link.hpp"

// TYPES

#include "Types/CompoMe/String.hpp"
// STRUCT

// PORT

#include "Ports/CompoMe/Stream/in.hpp"

#include "Ports/CompoMe/Stream/map_in.hpp"

namespace CompoMe {

namespace Zmq {

class Zmq_server_in : public CompoMe::Link {
public:
  Zmq_server_in();
  virtual ~Zmq_server_in();

  void step() override;
  void main_connect() override;
  void main_disconnect() override;

  // one connect
  void one_connect(CompoMe::Require_helper &, CompoMe::String c) override;
  void one_connect(CompoMe::Interface &, CompoMe::String) override;

  // one disconnect
  void one_disconnect(CompoMe::Require_helper &, CompoMe::String) override;
  void one_disconnect(CompoMe::Interface &, CompoMe::String) override;

  // Get and set /////////////////////////////////////////////////////////////

  CompoMe::String get_bind_addr() const;
  void set_bind_addr(const CompoMe::String bind_addr);
  CompoMe::String &a_bind_addr();

  // Get Port /////////////////////////////////////////////////////////////

  CompoMe::Stream::in &get_main();
  CompoMe::Stream::map_in &get_many();

public:
  // Function
  // ///////////////////////////////////////////////////////////////////

private:
  void *a_context;
  void *a_responder;

  // DATA ////////////////////////////////////////////////////////////////////
  CompoMe::String bind_addr;

  // PORT ////////////////////////////////////////////////////////////////////
  CompoMe::Stream::in main;
  CompoMe::Stream::map_in many;
};

} // namespace Zmq

} // namespace CompoMe
