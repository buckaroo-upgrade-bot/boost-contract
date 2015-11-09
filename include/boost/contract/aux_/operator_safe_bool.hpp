
#ifndef BOOST_CONTRACT_AUX_OPERATOR_SAFE_BOOL_HPP_
#define BOOST_CONTRACT_AUX_OPERATOR_SAFE_BOOL_HPP_

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

// This code is inspired by "boost/shared_ptr/detail/operator_bool.hpp".
    
/* PRIVATE */

// operator! is redundant, but some compilers need it.
#define BOOST_CONTRACT_OPERATOR_SAFE_BOOL_NOT_(bool_expr) \
    bool operator!() const BOOST_NOEXCEPT { return !(bool_expr); }

/* PUBLIC */

#if !defined(BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS) && \
        !defined(BOOST_NO_CXX11_NULLPTR)

#define BOOST_CONTRACT_AUX_OPERATOR_SAFE_BOOL(this_type, bool_expr) \
    explicit operator bool() const BOOST_NOEXCEPT { return (bool_expr); } \
    BOOST_CONTRACT_OPERATOR_SAFE_BOOL_NOT_(bool_expr)

#elif (defined(__SUNPRO_CC) && BOOST_WORKAROUND(__SUNPRO_CC, < 0x570) ) || \
        defined(__CINT__)

#define BOOST_CONTRACT_AUX_OPERATOR_SAFE_BOOL(this_type, bool_expr) \
    operator bool() const BOOST_NOEXCEPT { return (bool_expr); } \
    BOOST_CONTRACT_OPERATOR_SAFE_BOOL_NOT_(bool_expr)

#elif defined(_MANAGED)

#define BOOST_CONTRACT_AUX_OPERATOR_SAFE_BOOL(this_type, bool_expr) \
    static void boost_contract_aux_operator_safe_bool_func(this_type***) {} \
    typedef void (*boost_contract_aux_operator_safe_bool_type)(this_type***); \
    operator boost_contract_aux_operator_safe_bool_type() \
            const BOOST_NOEXCEPT { \
        return (bool_expr) ? &boost_contract_aux_operator_safe_bool_func : 0; \
    } \
    BOOST_CONTRACT_OPERATOR_SAFE_BOOL_NOT_(bool_expr)

#elif (defined(__MWERKS__) && BOOST_WORKAROUND(__MWERKS__, < 0x3200)) || \
        (defined(__GNUC__) && (__GNUC__ * 100 + __GNUC_MINOR__ < 304)) || \
        (defined(__SUNPRO_CC) && BOOST_WORKAROUND(__SUNPRO_CC, <= 0x590))

#define BOOST_CONTRACT_AUX_OPERATOR_SAFE_BOOL(this_type, bool_expr) \
    void boost_contract_aux_operator_safe_bool_func() const {} \
    typedef void (this_type::*boost_contract_aux_operator_safe_bool_type)() \
            const; \
    operator boost_contract_aux_operator_safe_bool_type() \
            const BOOST_NOEXCEPT { \
        return (bool_expr) ? \
                &this_type::boost_contract_aux_operator_safe_bool_func : 0; \
    } \
    BOOST_CONTRACT_OPERATOR_SAFE_BOOL_NOT_(bool_expr)

#else

#define BOOST_CONTRACT_AUX_OPERATOR_SAFE_BOOL(this_type, bool_expr) \
    void* boost_contract_aux_operator_safe_bool_data; \
    typedef void* this_type::*boost_contract_aux_operator_safe_bool_type; \
    operator boost_contract_aux_operator_safe_bool_type() \
            const BOOST_NOEXCEPT { \
        return (bool_expr) ? \
                &this_type::boost_contract_aux_operator_safe_bool_data : 0; \
    } \
    BOOST_CONTRACT_OPERATOR_SAFE_BOOL_NOT_(bool_expr)

#endif

#endif // #include guard

