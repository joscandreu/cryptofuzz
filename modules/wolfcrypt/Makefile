all: module.a

CXXFLAGS += -Wall -Wextra -Werror -std=c++17 -I ../../include -I ../../fuzzing-headers/include -DFUZZING_HEADERS_NO_IMPL -DCRYPTOFUZZ_WOLFCRYPT_ALLOCATION_FAILURES

module.a: module.o bn_ops.o
	test $(WOLFCRYPT_LIBWOLFSSL_A_PATH)
	rm -rf module.a
	rm -rf tmp/
	mkdir tmp/
	cd tmp && ar x $(WOLFCRYPT_LIBWOLFSSL_A_PATH)
	ar rcs module.a module.o bn_ops.o tmp/*
	ranlib module.a
bn_ops.o : bn_ops.cpp bn_ops.h
	$(CXX) $(CXXFLAGS) -I $(WOLFCRYPT_INCLUDE_PATH) -fPIC -c bn_ops.cpp -o bn_ops.o
module.o: module.cpp module.h
	test $(WOLFCRYPT_INCLUDE_PATH)
	$(CXX) $(CXXFLAGS) -I $(WOLFCRYPT_INCLUDE_PATH) -fPIC -c module.cpp -o module.o
clean:
	rm -rf *.o module.a
