#include <iostream>
#include <fstream>
#include "Vec3.h"
#include "ray.h"
#include "hittablelist.h"
#include "Sphere.h"
#include "float.h"
#include "camera.h"
#include "random.h"
#include "material.h"

using namespace std;


Vec3 color(const ray& r, hittable *world) {
hit_record rec;
if (world->hit(r, 0.0, MAXFLOAT, rec)) {
 Vec3 target = rec.p + rec.normal + random_in_unit_sphere();
 return 0.5 * color(ray(rec.p, target - rec.p), world);
 }
 else {
 Vec3 unit_direction = unitVector(r.direction());
 float t = 0.5*(unit_direction.y() + 1.0);
 return (1.0-t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);
 }
 }

//         Vec3 target = rec.p + rec.normal + random_in_unit_sphere();
//         return 0.5 * color(ray(rec.p, target - rec.p), world);
//         else {
//     Vec3 unit_direction = unitVector(r.direction());
//     float t = 0.5*(unit_direction.y() + 1.0);
//     return (1.0-t)*Vec3(1.0, 1.0, 1.0) + t*Vec3(0.5, 0.7, 1.0);
//     }
// };


int main()
{
    std::ofstream output;
    output.open("output.ppm");


    int nx = 200;
    int ny = 100;
    int ns = 100;
    output << "P3\n" << nx << " " << ny << "\n255\n";

    hittable *list[4];
    list[0] = new sphere(Vec3(0, 0, -1), 0.5, new lambertian(Vec3(0.8, 0.3, 0.3)));
    list[1] = new sphere(Vec3(0, -100.5,-1), 100, new lambertian(Vec3(0.8, 0.8, 0.0)));
    list[2] = new sphere(Vec3(1, 0, -1), 0.5, new metal(Vec3(0.8, 0.6, 0.2)));
    list[3] = new sphere(Vec3(-1, 0, -1), 0.5, new metal(Vec3(0.8, 0.8, 0.8)));
    hittable *world = new hittable_list(list, 4);

    camera cam;
    for (int j = ny-1; j >= 0; j--)
    {
            for (int i = 0; i < nx; ++i) {
                Vec3 col (0, 0, 0);
                for (int s = 0; s < ns; s++) {
                    float u = float(i + random_double()) / float(nx);
                    float v = float(j + random_double()) / float(ny);
                    ray r = cam.get_ray(u, v);
                    col += color(r, world);
                }
                //float u = float(i) / float(nx);
               // float v = float(j) / float(ny);
                //ray r(origin, lower_left_corner + u*horizontal + v*vertical);
               // Vec3 p = r.point_at_parameter(2.0);
                //Vec3 col = color(r, world);
                col /= float(ns);
                col = Vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );
                int ir = int(255.99*col[0]);
                int ig = int(255.99*col[1]);
                int ib = int(255.99*col[2]);

                output << ir << ' ' << ig << ' ' << ib << '\n';
            }
    }
    
    std::cerr << "\nDone.\n";
    output.close();
    return 0;
}