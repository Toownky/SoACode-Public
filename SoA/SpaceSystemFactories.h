///
/// SpaceSystemFactories.h
/// Seed of Andromeda
///
/// Created by Benjamin Arnold on 13 Jan 2015
/// Copyright 2014 Regrowth Studios
/// All Rights Reserved
///
/// Summary:
/// Component and entity factories for SpaceSystem
///

#pragma once

#ifndef SpaceSystemFactories_h__
#define SpaceSystemFactories_h__

class SpaceSystem;

#include <Vorb/ecs/Entity.h>
#include <Vorb/VorbPreDecl.inl>

class SoaState;
class PlanetGenData;

DECL_VG(
    class GLProgram;
    class TextureRecycler;
)
DECL_VVOX(class VoxelMapData);

namespace SpaceSystemFactories {
    /************************************************************************/
    /* Entity Factories                                                     */
    /************************************************************************/
   
    /// Planet entity
    extern vcore::EntityID createPlanet(OUT SpaceSystem* spaceSystem,
                                        const SystemBodyKegProperties* sysProps,
                                        const PlanetKegProperties* properties,
                                        SystemBody* body);
    extern void destroyPlanet(OUT SpaceSystem* gameSystem, vcore::EntityID planetEntity);

    /************************************************************************/
    /* Component Factories                                                  */
    /************************************************************************/
    /// Spherical voxel component
    extern vcore::ComponentID addSphericalVoxelComponent(OUT SpaceSystem* spaceSystem, vcore::EntityID entity,
                                                         vcore::ComponentID sphericalTerrainComponent,
                                                         const vvox::VoxelMapData* startingMapData,
                                                         const f64v3& gridPosition,
                                                         const SoaState* soaState);
    extern void removeSphericalVoxelComponent(OUT SpaceSystem* spaceSystem, vcore::EntityID entity);

    /// Axis rotation component
    extern vcore::ComponentID addAxisRotationComponent(OUT SpaceSystem* spaceSystem, vcore::EntityID entity,
                                                         const f64q& axisOrientation,
                                                         f64 startAngle,
                                                         f64 angularSpeed);
    extern void removeAxisRotationComponent(OUT SpaceSystem* spaceSystem, vcore::EntityID entity);

    /// Spherical terrain component
    extern vcore::ComponentID addSphericalTerrainComponent(OUT SpaceSystem* spaceSystem, vcore::EntityID entity,
                                                           vcore::ComponentID npComp,
                                                           vcore::ComponentID arComp,
                                                           f64 radius, PlanetGenData* planetGenData,
                                                           vg::GLProgram* normalProgram,
                                                           vg::TextureRecycler* normalMapRecycler);
    extern void removeSphericalTerrainComponent(OUT SpaceSystem* spaceSystem, vcore::EntityID entity);
}

#endif // SpaceSystemFactories_h__