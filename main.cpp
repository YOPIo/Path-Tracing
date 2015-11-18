#include "render.h"

int main(int argc, const char * argv[])
{
    RayTracing::render("cornellBox.ppm", 480, 480, 4, 8, 16);
    return 0;
}
