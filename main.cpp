#include <stdlib.h> 
#include <unistd.h>
#include <stdint.h>
#include <inttypes.h>

#include <stdio.h>

#include "include/CDK.h"
#include "include/CDKMsg.h"

int main() {
    const char* strVersion;
    strVersion = CDKGetVersion();
    printf("%s", strVersion);
    printf("\n");

    return 0;
}