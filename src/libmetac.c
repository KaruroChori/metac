#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include <stddef.h>

#include <sys/wait.h>
#include <dlfcn.h>
#include <libgen.h>
#include <sys/stat.h>

static char* run_command_and_capture_output(const char* command, int* status);
static void unquote_if_needed(char* str) ;

typedef struct {
    const char* ptr;
    size_t len;
} StringView;

void $__metac_error(const char* filename, int line, const char* str ){
    fprintf(stderr,"[ERROR] at %s, line %d: %s\n",filename,line,str);
    exit(1);
}

// --- Default runtime serializers ---
StringView _metac_serialize_int(int v) { int n=snprintf(NULL,0,"%d",v); char* s=malloc(n+1); snprintf(s,n+1,"%d",v); return (StringView){s,n}; }
StringView _metac_serialize_long(long v) { int n=snprintf(NULL,0,"%ld",v); char* s=malloc(n+1); snprintf(s,n+1,"%ld",v); return (StringView){s,n}; }
StringView _metac_serialize_float(float v) { int n=snprintf(NULL,0,"%f",v); char* s=malloc(n+1); snprintf(s,n+1,"%f",v); return (StringView){s,n}; }
StringView _metac_serialize_double(double v) { int n=snprintf(NULL,0,"%f",v); char* s=malloc(n+1); snprintf(s,n+1,"%f",v); return (StringView){s,n}; }
StringView _metac_serialize_const_char_ptr(const char* v) { if(!v) return (StringView){NULL,0}; size_t n=strlen(v); char* s=malloc(n+1); memcpy(s,v,n+1); return (StringView){s,n}; }

StringView _metac_strcpy(void* src, size_t len){
    char* s = malloc(len + 1);
    if (s) { memcpy(s, src, len + 1); }
    return (StringView){s, len};
}

StringView _metac_exec_eval(const char* filename, int line_num, const char* cmd){
    char* unquoted_cmd = strdup(cmd); 
    unquote_if_needed(unquoted_cmd);
    int status;
    char* expr_from_cmd = run_command_and_capture_output(unquoted_cmd, &status);
    if (status != 0) {
        fprintf(stderr, "Error: $exec_eval at %s:%d failed: %s\n", filename, line_num, expr_from_cmd);
        free(expr_from_cmd);
        free(unquoted_cmd);
        exit(1);
    } 

    free(unquoted_cmd);
    return (StringView){expr_from_cmd,strlen(expr_from_cmd)};
}

StringView _metac_exec_emit(const char* filename, int line_num, const char* cmd){
    char* unquoted_cmd = strdup(cmd); 
    unquote_if_needed(unquoted_cmd);
    int status;
    char* expr_from_cmd = run_command_and_capture_output(unquoted_cmd, &status);
    if (status != 0) {
        fprintf(stderr, "Error: $exec_emit at %s:%d failed: %s\n", filename, line_num, expr_from_cmd);
        free(expr_from_cmd);
        free(unquoted_cmd);
        exit(1);
    } 

    free(unquoted_cmd);
    return (StringView){expr_from_cmd,strlen(expr_from_cmd)};
}


static char* run_command_and_capture_output(const char* command, int* status) {
    char full_command[4096];
    snprintf(full_command, sizeof(full_command), "%s 2>&1", command);
    FILE* pipe = popen(full_command, "r");
    if (!pipe) {
        perror("popen failed");
        *status = -1;
        return strdup("");
    }
    size_t capacity = 4096, size = 0;
    char* output = malloc(capacity);
    if (!output) {
        perror("malloc");
        *status = -1;
        pclose(pipe);
        return strdup("");
    } 
    output[0] = '\0';
    while (!feof(pipe)) {
        size_t read_bytes = fread(output + size, 1, capacity - size - 1, pipe);
        if (read_bytes > 0) size += read_bytes;
        if (size >= capacity - 1) {
            capacity *= 2;
            char* new_output = realloc(output, capacity);
            if (!new_output) {
                free(output);
                perror("realloc failed");
                *status = -1;
                pclose(pipe);
                return strdup("");
            }
            output = new_output;
        }
    }
    output[size] = '\0';
    int pclose_status = pclose(pipe);
    *status = WIFEXITED(pclose_status) ? WEXITSTATUS(pclose_status) : -1;
    return output;
}

// --- Supporting Helpers ---
static void unquote_if_needed(char* str) {
    if (!str) return;
    size_t len = strlen(str);
    if (len >= 2 && str[0] == '"' && str[len - 1] == '"'){
        memmove(str, str + 1, len - 2); str[len - 2] = '\0';
    }
}