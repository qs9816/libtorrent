/*

Copyright (c) 2006-2016, Arvid Norberg, Steven Siloti
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

* Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in
the documentation and/or other materials provided with the distribution.
* Neither the name of the author nor the names of its
contributors may be used to endorse or promote products derived
from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/

#ifndef KADEMLIA_IO_HPP
#define KADEMLIA_IO_HPP

#include "libtorrent/kademlia/node_id.hpp"
#include "libtorrent/socket_io.hpp"

namespace lt { namespace dht {

	struct node_endpoint
	{
		node_id id;
		udp::endpoint ep;
	};

	template<class InIt>
	node_endpoint read_node_endpoint(udp protocol, InIt&& in)
	{
#if !TORRENT_USE_IPV6
		TORRENT_UNUSED(protocol);
#endif
		node_endpoint ep;
		std::copy(in, in + 20, ep.id.begin());
		in += 20;
#if TORRENT_USE_IPV6
		if (protocol == udp::v6())
			ep.ep = detail::read_v6_endpoint<udp::endpoint>(in);
		else
#endif
			ep.ep = detail::read_v4_endpoint<udp::endpoint>(in);
		return ep;
	}

}}

#endif
