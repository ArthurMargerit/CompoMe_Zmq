#include "Links/CompoMe/Zmq/Zmq_server_in/Zmq_server_in.hpp"

namespace CompoMe {

namespace Zmq {

//============================= bind_addr =============================
CompoMe::String Zmq_server_in::get_bind_addr() const { return this->bind_addr; }

void Zmq_server_in::set_bind_addr(const CompoMe::String p_bind_addr) {
  this->bind_addr = p_bind_addr;
}

CompoMe::String &Zmq_server_in::a_bind_addr() { return this->bind_addr; }
//--------------------------------------------------------------------------

// Get Port /////////////////////////////////////////////////////////////

CompoMe::Stream::in &Zmq_server_in::get_main() { return this->main; }
CompoMe::Stream::map_in &Zmq_server_in::get_many() { return this->many; }

} // namespace Zmq

} // namespace CompoMe
