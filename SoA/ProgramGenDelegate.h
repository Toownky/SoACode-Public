///
/// ProgramGenDelegate.h
/// Seed of Andromeda
///
/// Created by Benjamin Arnold on 4 Feb 2015
/// Copyright 2014 Regrowth Studios
/// All Rights Reserved
///
/// Summary:
/// Delegate for generating a shader program
///

#pragma once

#ifndef ProgramGenDelegate_h__
#define ProgramGenDelegate_h__

#include <Vorb/RPC.h>
#include <Vorb/graphics/GLProgram.h>

class ProgramGenDelegate : public IDelegate < void* > {
public:
    virtual void invoke(Sender sender, void* userData) override {
        std::cout << "Building shader: " << name << std::endl;
        program = new vg::GLProgram(true);
        if (!program->addShader(vs)) {
            errorMessage = "Vertex shader for " + name + " failed to compile.";
            program->dispose();
            delete program;
            program = nullptr;
            return;
        }
        if (!program->addShader(fs)) {
            errorMessage = "Fragment shader for " + name + " failed to compile.";
            program->dispose();
            delete program;
            program = nullptr;
            return;
        }
        if (attr) program->setAttributes(*attr);

        if (!program->link()) {
            errorMessage = name + " failed to link.";
            program->dispose();
            delete program;
            program = nullptr;
            return;
        }
        program->initAttributes();
        program->initUniforms();
    }

    nString name;
    vg::ShaderSource vs;
    vg::ShaderSource fs;
    std::vector<nString>* attr = nullptr;

    vcore::RPC rpc;

    vg::GLProgram* program = nullptr;
    nString errorMessage;
};

#endif // ProgramGenDelegate_h__
