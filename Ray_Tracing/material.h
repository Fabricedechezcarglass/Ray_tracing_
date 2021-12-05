#ifndef MATERIALH
#define MATERIALH

#include <iostream>
#include "Vec3.h"
#include "ray.h"
#include "hittable.h"

class material {
    public:
        virtual bool scatter(
            const ray& r_in, const hit_record& rec, Vec3& attenuation, ray& scattered) const = 0;
};

class lambertian : public material {
    public:
        lambertian(const Vec3& a) : albedo(a) {}
        virtual bool scatter(const ray& r_in, const hit_record& rec,
        Vec3& attenuation, ray& scattered) const {
            Vec3 target = rec.p + rec.normal + random_in_unit_sphere();
            scattered = ray(rec.p, target-rec.p);
            attenuation = albedo;
            return true;
        }

        Vec3 albedo;
};

class metal : public material {
    public:
        metal(const Vec3& a) : albedo(a) {}
        virtual bool scatter(const ray& r_in, const hit_record& rec,
                                Vec3& attenuation, ray& scattered) const {
                    Vec3 reflected = reflect(unitVector(r_in.direction()), rec.normal);
                    scattered = ray(rec.p, reflected);
                    attenuation = albedo;
                    return (dot(scattered.direction(), rec.normal) > 0);
        }
    Vec3 albedo;
};
#endif