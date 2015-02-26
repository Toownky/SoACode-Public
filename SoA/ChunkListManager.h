///
/// ChunkListManager.h
/// Seed of Andromeda
///
/// Created by Benjamin Arnold on 26 Feb 2015
/// Copyright 2014 Regrowth Studios
/// All Rights Reserved
///
/// Summary:
/// Manages chunk state lists
///

#pragma once

#ifndef ChunkListManager_h__
#define ChunkListManager_h__

#include "Chunk.h"

class ChunkListManager {
public:
    /// Adds a chunk to the setupList
    /// @param chunk: the chunk to add
    void addToSetupList(Chunk* chunk);
    /// Adds a chunk to the loadList
    /// @param chunk: the chunk to add
    void addToLoadList(Chunk* chunk);
    /// Adds a chunk to the meshList
    /// @param chunk: the chunk to add
    void addToMeshList(Chunk* chunk);
    /// Adds a chunk to the generateList
    /// @param chunk: the chunk to add
    void addToGenerateList(Chunk* chunk);

    /// Stack of chunks needing setup
    std::vector<ChunkID> setupList;
    /// Stack of chunks that need to be meshed on the threadPool
    std::vector<ChunkID> meshList;
    /// Stack of chunks that need to be sent to the IO thread
    std::vector<ChunkID> loadList;
    /// Stack of chunks needing generation
    std::vector<ChunkID> generateList;
};

#endif // ChunkListManager_h__
