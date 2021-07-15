#pragma once

#include "Data/CompoMe_Zmq.hpp"

#include "Links/Link.hpp"
#include "Links/CompoMe/Posix/Fake_pack.hpp"
// TYPES

#include "Types/CompoMe/String.hpp"
// STRUCT

// PORT

#include "Ports/CompoMe/Stream/out.hpp"

#include "Ports/CompoMe/Stream/map_out.hpp"

namespace CompoMe {

namespace Zmq {

class Zmq_client_out : public CompoMe::Link {
public:
  Zmq_client_out();
  virtual ~Zmq_client_out();

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

  CompoMe::String get_addr() const;
  void set_addr(const CompoMe::String addr);
  CompoMe::String &a_addr();

  // Get Port /////////////////////////////////////////////////////////////

  CompoMe::Stream::out &get_main();
  CompoMe::Stream::map_out &get_many();

public:
  // Function
  // ///////////////////////////////////////////////////////////////////

private:
  void *a_context;
  void *a_requester;
  std::map<CompoMe::String, struct CompoMe::Posix::Fake_pack> fake_many;


  // DATA ////////////////////////////////////////////////////////////////////
  CompoMe::String addr;

  // PORT ////////////////////////////////////////////////////////////////////
  CompoMe::Stream::out main;
  CompoMe::Stream::map_out many;

};

} // namespace Zmq

} // namespace CompoMe
