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

class Zmq_server_component_interface_in : public CompoMe::Link,
                                          public CompoMe::Link_map_map_in {
public:
  Zmq_server_component_interface_in();
  virtual ~Zmq_server_component_interface_in();

  void step() override;
  void connect() override;
  void disconnect() override;

  // Get and set /////////////////////////////////////////////////////////////

  virtual CompoMe::String get_bind_addr() const;
  virtual void set_bind_addr(const CompoMe::String bind_addr);

public:
  // Function
  // ///////////////////////////////////////////////////////////////////
private:
  void *a_context;
  void *a_responder;

  // DATA ////////////////////////////////////////////////////////////////////

  CompoMe::String bind_addr;
};

} // namespace Zmq

} // namespace CompoMe
