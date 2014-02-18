//
// factory.hpp
//
// Author: 	Lutz Bichler
//
// This file is part of the BMW Some/IP implementation.
//
// Copyright © 2013, 2014 Bayerische Motoren Werke AG (BMW).
// All rights reserved.
//

#ifndef VSOMEIP_FACTORY_HPP
#define VSOMEIP_FACTORY_HPP

#include <vsomeip/enumeration_types.hpp>
#include <vsomeip/primitive_types.hpp>

namespace vsomeip {

class application;
class message;
class endpoint;
class serializer;
class deserializer;

class factory {
public:
	static factory * get_default_factory();
	virtual ~factory() {};

	virtual application * create_application() const = 0;

	virtual message * create_message() const = 0;

	virtual endpoint * get_endpoint(
							ip_address _address, ip_port _port,
							ip_protocol _protocol, ip_version _version) = 0;

	virtual serializer * create_serializer() const = 0;
	virtual deserializer * create_deserializer() const = 0;
};

}; // namespace vsomeip

#endif // VSOMEIP_FACTORY_HPP
