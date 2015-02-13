
#ifndef BOOST_CONTRACT_EXT_PP_KEYWORD_TRAITS_HPP_
#define BOOST_CONTRACT_EXT_PP_KEYWORD_TRAITS_HPP_

#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/expand.hpp>

/* PUBLIC */

// Expand decl = `[keyword] ...` to `(..., [keyword] EMPTY)`.
// Precondition: `...` in decl cannot be EMPTY() (so expanded 2-tuple is valid).
#define BOOST_CONTRACT_EXT_PP_KEYWORD1_TRAITS_PARSE( \
    decl, \
    keyword1, is_keyword1_macro, remove_keyword1_macro \
) \
    BOOST_PP_EXPAND( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_TRAITS_ \
        BOOST_PP_IIF(is_keyword1_macro(decl), \
            (BOOST_CONTRACT_EXT_PP_KEYWORD_TRAITS_YES_, decl, \
            keyword1, remove_keyword1_macro) \
        , \
            (BOOST_CONTRACT_EXT_PP_KEYWORD_TRAITS_NO_, decl, ~, ~) \
        ) \
    )

// Expand decl = `[keyword] ...` to `(..., [keyword] EMTPY)`, where keyword can
// be one among 3 possible keywords.
// Precondition: `...` in decl cannot be EMPTY() (so expanded 2-tuple is valid).
#define BOOST_CONTRACT_EXT_PP_KEYWORD3_TRAITS_PARSE( \
    decl, \
    keyword1, is_keyword1_macro, remove_keyword1_macro, \
    keyword2, is_keyword2_macro, remove_keyword2_macro, \
    keyword3, is_keyword3_macro, remove_keyword3_macro \
) \
    BOOST_PP_EXPAND( \
        BOOST_CONTRACT_EXT_PP_KEYWORD_TRAITS_ \
        BOOST_PP_IIF(is_keyword1_macro(decl), \
            (BOOST_CONTRACT_EXT_PP_KEYWORD_TRAITS_YES_, decl, \
            keyword1, remove_keyword1_macro) \
        , BOOST_PP_IIF(is_keyword2_macro(decl), \
            (BOOST_CONTRACT_EXT_PP_KEYWORD_TRAITS_YES_, decl, \
            keyword2, remove_keyword2_macro) \
        , BOOST_PP_IIF(is_keyword3_macro(decl), \
            (BOOST_CONTRACT_EXT_PP_KEYWORD_TRAITS_YES_, decl, \
            keyword3, remove_keyword3_macro) \
        , \
            (BOOST_CONTRACT_EXT_PP_KEYWORD_TRAITS_NO_, decl, ~, ~) \
        ))) \
    )

/* PRIVATE */

#define BOOST_CONTRACT_EXT_PP_KEYWORD_TRAITS_(macro, _1, _2, _3) \
    macro(_1, _2, _3)

// Precondition: decl = `keyword ...`.
#define BOOST_CONTRACT_EXT_PP_KEYWORD_TRAITS_YES_( \
        decl, keyword, remove_keyword_macro) \
    (remove_keyword_macro(decl), keyword BOOST_PP_EMPTY)

#define BOOST_CONTRACT_EXT_PP_KEYWORD_TRAITS_NO_(decl, unsued1, unused2) \
    (decl, BOOST_PP_EMPTY)

#endif // #include guard

