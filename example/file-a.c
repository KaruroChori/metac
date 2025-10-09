#include <string.h>

#include <metac/string_view.h>
#include <metac/comptime.h>

extern void* png_create_info_struct(void*);

int test1(){
    png_create_info_struct(NULL);
    return $eval(int, 43);
}