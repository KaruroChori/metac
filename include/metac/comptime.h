#pragma once

#ifndef $COMPTIME_ERASE

    #ifdef $COMPTIME

    extern void $__metac_error(const char* filename, int line, const char* str );
    #define $comptime_error(x) $__metac_error(__FILE__, __LINE__, x )

    #define $eval(type,expr) ($comptime_error("Cannot use $eval at compiletime"),(type){})
    #define $emit(stmt) $comptime_error("Cannot use $emit at compiletime")
    #define $exec_eval(type,expr) ($comptime_error("Cannot use $exec_eval at compiletime"),(type){})
    #define $exec_emit(stmt) $comptime_error("Cannot use $exec_emit at compiletime")
    #define $comptime(stmt) stmt

    #else

    extern void $__metac_error(const char* filename, int line, const char* str );

    #define $comptime_error(x) $__metac_error(__FILE__, __LINE__, x )

    #define $eval(type,expr) ($comptime_error("Your compiler has no support for $eval"),(type){})
    #define $emit(stmt) $comptime_error("Your compiler has no support for $emit")
    #define $exec_eval(type,expr) ($comptime_error("Your compiler has no support for $exec_eval"),(type){})
    #define $exec_emit(stmt) $comptime_error("Your compiler has no support for $exec_emit")
    #define $comptime(stmt)
    #endif

#endif