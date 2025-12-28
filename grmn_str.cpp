#include <iostream>
#include <cstring>
using namespace std;

struct GermanString {
    int len;
    union {
        char short_data[12];
        struct {
            char prefix[4];
            const char* ptr;
        } long_data;
    };
    GermanString(const char* s) {
        len=strlen(s);
        if (len<=12) {
            memcpy(short_data, s, len);
            if (len<12) { short_data[len] = '\0'; }
        } 
        else {
            memcpy(long_data.prefix, s, 4);
            long_data.ptr = s;
        }
    }
};
bool operator==(const GermanString& a, const GermanString& b) {
    if (a.len!=b.len) return false;
    if (a.len<=12) { return memcmp(a.short_data, b.short_data, a.len) == 0; }
    const char* ap=a.long_data.prefix;
    const char* bp=b.long_data.prefix;
    if (memcmp(ap, bp, 4) != 0) return false;
    return strcmp(a.long_data.ptr, b.long_data.ptr)==0;
}
GermanString operator+(const GermanString& a, const GermanString& b) {
    char* tmp= new char[a.len+b.len + 1];
    if (a.len<=12) {
        memcpy(tmp, a.short_data, a.len);
    }
    else {
        memcpy(tmp, a.long_data.ptr, a.len);
    }
    if (b.len<=12) {
        memcpy(tmp+a.len, b.short_data, b.len);
    }
    else {
        memcpy(tmp+a.len, b.long_data.ptr, b.len);
    }
    tmp[a.len+b.len]='\0';
    return GermanString (tmp);
}
void print (GermanString a) {
    if (a.len<=12) {
        for (int i=0; i<a.len; i++) {
            cout<<a.short_data[i];
        }
    }
    else {
        for (int i=0; i<a.len; i++) {
            cout<<a.long_data.ptr[i];
        }
    }
}


int main() {
    GermanString a("hello");
    GermanString b("helloa");
    GermanString c("hellohelloa");
    cout<<(a==b)<<endl;
    cout<<(a==c)<<endl;
    GermanString d=a+b;
    cout<<(d==c)<<endl;
    print(a);
    cout<<endl;
    print(c);
}