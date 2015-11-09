#include "render.h"

int main(int argc, const char * argv[])
{
    Intersection::render("cornellBox.ppm", 480, 480, 4, 16, 16);
    return 0;
}
