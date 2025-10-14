#pragma once

#define include_wrp #include

#ifndef $COMPTIME_ERASE

    #ifdef $COMPTIME

    [[noreturn]] extern void $__metac_error(const char* filename, int line, const char* str );
    #define $comptime_error(x) $__metac_error(__FILE__, __LINE__, x )
    #define $comptime_only(x) x
    #define $if_comptime(x) x
    //#define $include_comptime(x)
    #define $eval(type,expr) ($comptime_error("Cannot use $eval at compiletime"),(type){})
    #define $emit(stmt) $comptime_error("Cannot use $emit at compiletime")
    #define $exec_eval(type,expr) ($comptime_error("Cannot use $exec_eval at compiletime"),(type){})
    #define $exec_emit(stmt) $comptime_error("Cannot use $exec_emit at compiletime")

    #else
    [[noreturn]] extern void exit(int);
    extern int printf(const char*, ...);
    [[noreturn]] static void $__metac_error(const char* filename, int line, const char* str ){printf(str);exit(1);}

    #define $comptime_error(x) $__metac_error(__FILE__, __LINE__, x )
    #define $comptime_only(x) $comptime_error("Function not available outside comptime.")
    #define $if_comptime(x)
    //#define $include_comptime(x)

    #define $eval(type,expr) ($comptime_error("Your compiler has no support for $eval"),(type){})
    #define $emit(stmt) $comptime_error("Your compiler has no support for $emit")
    #define $exec_eval(type,expr) ($comptime_error("Your compiler has no support for $exec_eval"),(type){})
    #define $exec_emit(stmt) $comptime_error("Your compiler has no support for $exec_emit")
    #endif
#else
#endif
