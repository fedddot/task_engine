#include <iostream>
#include <string>

#include "gtest/gtest.h"

#include "integer.hpp"
#include "string.hpp"
#include "object.hpp"
#include "json_data_serializer.hpp"

using namespace engine;
using namespace engine_utl;

TEST(ut_json_data_serializer, serialize_sanity) {
	// GIVEN:
	Object data;
	data.add("key1", String("val1"));
	data.add("key2", Integer(12));
	Object nested_data;
	nested_data.add("key3", String("val2"));
	nested_data.add("key4", Integer(34));
	data.add("nested_data", nested_data);

	// WHEN:
	JsonDataSerializer instance;
	std::string result;

	// THEN:
	ASSERT_NO_THROW(result = instance.serialize(data));
	std::cout << result << std::endl;
}