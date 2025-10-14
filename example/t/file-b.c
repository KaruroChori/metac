#include "../../include/metac/string_view.h"
#include "../../include/metac/comptime.h"

extern int test1();
int test2(){return 22;}

#include <stdio.h>
#include <stdlib.h>

// --- For testing $eval with a custom type ---

// 1. Define a custom struct.
typedef struct {
    int id;
    const char* name;
} User;

// 2. Provide the required serializer for the 'User' type.
// The name must be `_metac_serialize_<sanitized_type_name>`.
StringView _metac_serialize_User(User u) {
    int n = snprintf(NULL, 0, "(User){.id=%d, .name=\"%s\"}", u.id, u.name);
    char* s = malloc(n + 1);
    snprintf(s, n + 1, "(User){.id=%d, .name=\"%s\"}", u.id, u.name);
    return (StringView){.ptr = s, .len = n};
}

// 3. A helper function used inside an $eval expression.
const char* get_username() {
    return "Alice";
}


$if_comptime(
#include <md4.h>
)

//#define $include_comptime $include_comptime

//$include_comptime("md4.h")


static inline int answer_to_life(int a, int b){
    $comptime_only(
        return 42;
    );
}


// --- Main test function ---

void run_all_tests() {

    int int_view = $eval(int, answer_to_life(1,5));

    User user_view = $eval(User, ((User){ .id = 101,
         .name = get_username() }));


    User user_view2 = $eval(User, ((User){ .id = 101,
         .name = get_username() }));

    $emit(for (int i=0; i<2; ++i) { puts("Hello from $emit!"); });

    int int_eval = $exec_eval(int, "./get_version.sh");
    $exec_emit("./get_banner.sh");


    $emit(struct help{};for (int i=0; i<2; ++i) { puts("Hello from $emit!"); });

    /*$exec_emit("./get_banner.sh");*/

    /* $exec_emit("uname -a"); */
    answer_to_life(4,6);
}

int main() {
    run_all_tests();
    return test1();
}