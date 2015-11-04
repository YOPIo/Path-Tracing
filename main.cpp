#include "render.h"

int main(int argc, const char * argv[])
{
    Intersection::render("cornellBox3.ppm", 640, 480, 1, 4, 16);
    return 0;
}
