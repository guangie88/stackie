/**
 * Stack allocated string implementation.
 * @author Chen Weiguang
 * @version 0.1.0
 */

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <ostream>
#include <string>

namespace stackie {

    // declaration section

    /**
     * Represent stack allocated string with a given max number of chars
     * that it can possibly store.
     * All methods have noexcept specifications.
     * @tparam N Max number of chars EXCLUDING the null terminator char.
     */
    template <size_t N>
    class sstring {
    public:
        /**
         * Create an empty stack allocated string with no characters.
         */
        sstring() noexcept;

        /**
         * Initialize by copying up to min(N, M) characters from the given stack allocated string rhs.
         * If M > N, truncation will take place.
         * The min(N, M)th character will always be a null char.
         * @param rhs Another stack allocated string to copy from.
         */
        template <size_t M>
        sstring(const sstring<M> &rhs) noexcept;

        /**
         * Initialize by copying up to min(N, M) characters from the
         * given char array of known compile time length rhs.
         * If M > N, truncation will take place.
         * The min(N, M)th character will always be a null char.
         * @param rhs Null terminated char array to copy from.
         */
        template <size_t M>
        sstring(const char (&rhs)[M]) noexcept;

        /**
         * Initialize by copying up to min(N, strlen(rhs)) characters from the given char array rhs.
         * If strlen(rhs) > N, truncation will take place.
         * The min(N, strlen(rhs))th character will always be a null char.
         * @param rhs Null terminated char array to copy from.
         */
        sstring(const char rhs[]) noexcept;

        /**
         * Initialize by copying up to min(N, rhs.length()) characters from the given char array rhs.
         * If rhs.length() > N, truncation will take place.
         * The min(N, rhs.length())th character will always be a null char.
         * @param rhs Char array to copy from.
         */
        sstring(const std::string &rhs) noexcept;

        /**
         * Assign up to min(N, M) characters from the given stack allocated string rhs.
         * If M > N, truncation will take place.
         * The min(N, M)th character will always be a null char.
         * @param rhs Another stack allocated string to copy from.
         */
        template <size_t M>
        auto operator=(const sstring<M> &rhs) noexcept -> sstring &;

        /**
         * Assign by copying up to min(N, M) characters from the
         * given char array of known compile time length rhs.
         * If M > N, truncation will take place.
         * The min(N, M)th character will always be a null char.
         * @param rhs Null terminated char array to copy from.
         */
        template <size_t M>
        auto operator=(const char (&rhs)[M]) noexcept -> sstring &;

        /**
         * Assign up to min(N, strlen(rhs)) characters from the given char array rhs.
         * If strlen(rhs) > N, truncation will take place.
         * The min(N, strlen(rhs))th character will always be a null char.
         * @param rhs Null terminated char array to copy from.
         * @return Self in reference form.
         */
        auto operator=(const char rhs[]) noexcept -> sstring &;

        /**
         * Initialize by copying up to min(N, rhs.length()) characters from the given char array rhs.
         * If rhs.length() > N, truncation will take place.
         * The min(N, rhs.length())th character will always be a null char.
         * @param rhs Char array to copy from.
         */
        auto operator=(const std::string &rhs) noexcept -> sstring &;

        /**
         * Get the char array inner representation in immutable form.
         * This is potentially an unsafe operation.
         * @return Inner char array representation.
         */
        auto c_str() const noexcept -> const char *;

        /**
         * Gets the compile time capacity of the stack allocated string.
         * @return Compile time capacity.
         */
        static constexpr auto capacity() noexcept -> size_t;

        /**
         * Gets the number of chars stored.
         * The length can only be less or equal to capacity().
         * @return Number of chars stored.
         */
        auto length() const noexcept -> size_t;

    private:
        /** Hold the char array value with null char. */
        char s[N + 1];
    };

    /**
     * Prints the inner representation of the stack allocated string
     * into output stream, similar to std::string.
     * @tparam N Capacity of sstring EXCLUDING the null terminator char.
     * @param stream Output stream to print into.
     * @param rhs Stack allocated string to print.
     * @return Output stream after printing in reference form.
     */
    template <size_t N>
    auto operator<<(std::ostream &stream, const sstring<N> &rhs) -> std::ostream &;

    // implementation section

    namespace details {
        /**
         * Copies from src to dst, with possibility of truncation if dst has capacity
         * smaller than src.
         * Meant to be only used by sstring.
         * @tparam N Capacity of sstring EXCLUDING the null terminator char.
         * @param src Source char array to copy from.
         * @param src_len Length of source char array.
         * @param dst Destination char array to copy into.
         */
        template <size_t N>
        void copy_n_impl(const char src[], const size_t src_len, char dst[]) noexcept {
            const auto min_len = std::min(src_len, N);
            std::copy_n(src, min_len, dst);
            dst[min_len] = '\0';
        }
    }

    template <size_t N>
    sstring<N>::sstring() noexcept {
        s[0] = '\0';
    }

    template <size_t N>
    template <size_t M>
    sstring<N>::sstring(const sstring<M> &rhs) noexcept {
        *this = rhs;
    }

    template <size_t N>
    template <size_t M>
    sstring<N>::sstring(const char (&rhs)[M]) noexcept {
        *this = rhs;
    }

    template <size_t N>
    sstring<N>::sstring(const char rhs[]) noexcept {
        *this = rhs;
    }

    template <size_t N>
    sstring<N>::sstring(const std::string &rhs) noexcept {
        *this = rhs;
    }

    template <size_t N>
    template <size_t M>
    auto sstring<N>::operator=(const sstring<M> &rhs) noexcept -> sstring & {
        details::copy_n_impl<N>(rhs.c_str(), M, s);
        return *this;
    }

    template <size_t N>
    template <size_t M>
    auto sstring<N>::operator=(const char (&rhs)[M]) noexcept -> sstring & {
        details::copy_n_impl<N>(rhs, M, s);
        return *this;
    }

    template <size_t N>
    auto sstring<N>::operator=(const char rhs[]) noexcept -> sstring & {
        details::copy_n_impl<N>(rhs, std::strlen(rhs), s);
        return *this;
    }

    template <size_t N>
    auto sstring<N>::operator=(const std::string &rhs) noexcept -> sstring & {
        details::copy_n_impl<N>(rhs.c_str(), rhs.length(), s);
        return *this;
    }

    template <size_t N>
    auto sstring<N>::c_str() const noexcept -> const char * {
        return s;
    }

    template <size_t N>
    constexpr auto sstring<N>::capacity() noexcept -> size_t {
        return N;
    }

    template <size_t N>
    auto sstring<N>::length() const noexcept -> size_t {
        return std::strlen(s);
    }

    template <size_t N>
    auto operator<<(std::ostream &stream, const sstring<N> &rhs) -> std::ostream & {
        return stream << rhs.c_str();
    }
}
