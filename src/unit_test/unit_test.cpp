#include "stackie/sstring.hpp"

#include <cstddef>
#include <cstring>
#include <sstream>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

static constexpr size_t SMALL_N = 8;
static constexpr size_t N = 256;
static constexpr auto NUL_CHAR = '\0';

using sstring8_t = stackie::sstring<SMALL_N>;
using sstring256_t = stackie::sstring<N>;

TEST_CASE("Default construct sstring", "[sstring_default_ctor]") {
    sstring256_t s;
    REQUIRE(s.capacity() == N);
    REQUIRE(s.length() == 0);
    REQUIRE(s.c_str()[0] == NUL_CHAR);
}

TEST_CASE("Copy construct sstring from char[M]", "[sstring_copy_ctor_char_m]") {
    static constexpr char MSG[] = "hello world!";
    sstring256_t s = MSG;
    REQUIRE(s.capacity() == N);

    const auto len = std::strlen(MSG);
    REQUIRE(s.length() == len);
    REQUIRE(s.c_str()[len] == NUL_CHAR);
}

TEST_CASE("Copy construct sstring from char[M] exceeding capacity", "[sstring_copy_ctor_char_m_exceed]") {
    static constexpr char MSG[] = "hello world!";
    sstring8_t s = MSG;
    REQUIRE(s.capacity() == SMALL_N);

    const auto len = std::strlen(MSG);
    REQUIRE(s.capacity() < len);
    REQUIRE(s.length() == s.capacity());

    REQUIRE(std::strncmp(s.c_str(), MSG, s.capacity()) == 0);
    REQUIRE(s.c_str()[s.capacity()] == NUL_CHAR);
}

TEST_CASE("Copy construct sstring from char *", "[sstring_copy_ctor_char_ptr]") {
    const std::string msg = "hello world!";
    sstring256_t s = msg.c_str();
    REQUIRE(s.capacity() == N);

    const auto len = msg.length();
    REQUIRE(s.length() == len);
    REQUIRE(s.c_str()[len] == NUL_CHAR);
}

TEST_CASE("Copy construct sstring from string", "[sstring_copy_ctor_string]") {
    const std::string msg = "hello world!";
    sstring256_t s = msg;
    REQUIRE(s.capacity() == N);

    const auto len = msg.length();
    REQUIRE(s.length() == len);
    REQUIRE(s.c_str()[len] == NUL_CHAR);
}

TEST_CASE("Assign sstring from char[M]", "[sstring_assign_char_m]") {
    static constexpr char MSG[] = "hello world!";
    sstring256_t s;
    s = MSG;
    REQUIRE(s.capacity() == N);

    const auto len = std::strlen(MSG);
    REQUIRE(s.length() == len);
    REQUIRE(s.c_str()[len] == NUL_CHAR);
}

TEST_CASE("Assign sstring from char[M] exceeding capacity", "[sstring_assign_char_m_exceed]") {
    static constexpr char MSG[] = "hello world!";
    sstring8_t s;
    s = MSG;
    REQUIRE(s.capacity() == SMALL_N);

    const auto len = std::strlen(MSG);    
    REQUIRE(s.capacity() < len);
    REQUIRE(s.length() == s.capacity());

    REQUIRE(std::strncmp(s.c_str(), MSG, s.capacity()) == 0);
    REQUIRE(s.c_str()[s.capacity()] == NUL_CHAR);
}

TEST_CASE("Assign sstring from char *", "[sstring_assign_char_ptr]") {
    const std::string msg = "hello world!";
    sstring256_t s;
    s = msg.c_str();
    REQUIRE(s.capacity() == N);

    const auto len = msg.length();
    REQUIRE(s.length() == len);
    REQUIRE(s.c_str()[len] == NUL_CHAR);
}

TEST_CASE("Assign sstring from string", "[sstring_assign_string]") {
    const std::string msg = "hello world!";
    sstring256_t s;
    s = msg;
    REQUIRE(s.capacity() == N);

    const auto len = msg.length();
    REQUIRE(s.length() == len);
    REQUIRE(s.c_str()[len] == NUL_CHAR);
}

TEST_CASE("Output stream from sstring", "[sstring_output_stream]") {
    static constexpr char MSG[] = "hello world!";
    sstring256_t s{MSG};
    REQUIRE(s.capacity() == N);

    const auto len = std::strlen(MSG);
    REQUIRE(s.length() == len);
    REQUIRE(s.c_str()[len] == NUL_CHAR);

    std::stringstream stream_s0;
    stream_s0 << s;

    std::stringstream stream_s1;
    stream_s1 << MSG;

    REQUIRE(stream_s0.str() == stream_s1.str());
}