#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <iostream>
#include <vector>
#include <memory>
#include "hittable.h"

using std::vector;
using std::shared_ptr;

class hittable_list : public hittable{

    vector< shared_ptr< hittable > > objects;
    public:    
    hittable_list(){}
    hittable_list( shared_ptr<hittable> object ){ 
        add_object( object );
    }

    void clear(){
        objects.clear();
    }
    void add_object( shared_ptr<hittable> object ){
        objects.push_back( object );
    }
    virtual bool hit( const ray& r, double tmin, double tmax, hit_record& hit ) const override;
};

bool hittable_list::hit(const ray& r, double tmin, double tmax, hit_record& rec) const {
    hit_record temp_record;
    bool hit_anything = false;
    auto closest_so_far = tmax;

    for( const auto& object : objects ){
        if(object->hit( r, tmin, closest_so_far, temp_record)){
            hit_anything = true;
            closest_so_far = temp_record.t;
            rec = temp_record;
        }
    }
    
    return hit_anything;
}

#endif