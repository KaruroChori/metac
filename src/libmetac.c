#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include <stddef.h>

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