/******************************************************************************/
/*!
\file		Agent.h
\project	CS380/CS580 AI Framework
\author		Dustin Holmes
\summary	Base actor declarations

Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
*/
/******************************************************************************/

#pragma once
#include "../Misc/NiceTypes.h"

// forward declarations
class AgentOrganizer;

class Agent
{
    friend class AgentOrganizer;
public:
    Agent(const char* type, size_t id);

#pragma region Getters
    const Vec3& get_position() const;
    const Vec3& get_scaling() const;

    Vec3 get_forward_vector() const;
    Vec3 get_right_vector() const;
    Vec3 get_up_vector() const;

    // in radians
    float get_pitch() const;
    float get_yaw() const;
    float get_roll() const;

    const Vec3& get_color() const;

    const Mat4& get_local_to_world();

    const char* get_type() const;
    const size_t& get_id() const;

    float get_movement_speed() const;

    Agent_ROLE get_AGrole() const { return ag_Role; }
    Agent* get_targetAgent() const { return targetAgent; }
    Agent* get_idealMatch() const { return idealMatch; }
    int get_Appeal() const { return Appeal; }
    int get_Confidence() const { return Confidence; }
    int get_Fulfilment() const { return Fulfilment; }
    bool get_DOA() const { return DOA; }
#pragma endregion

#pragma region Setters
    void set_position(const Vec3 &pos);
    void set_scaling(const Vec3 &scale);
    void set_scaling(float scalar);

    void set_pitch(float angleRadians);
    void set_yaw(float angleRadians);
    void set_roll(float angleRadians);

    void set_color(const Vec3 &newColor);
    
    void set_movement_speed(float speed);


    void set_AGrole(Agent_ROLE role) { ag_Role = role; }
    void set_targetAgent(Agent* tAgent) { targetAgent = tAgent; }
    void set_idealMatch(Agent* tAgent) { idealMatch = tAgent; }
    void set_Appeal(int value) { Appeal = value; }
    void set_Confidence(int value) { Confidence = value; }
    void set_Fulfilment(int value) { Fulfilment = value; }
    void set_DOA(bool doa) { DOA = doa; }
#pragma endregion

    virtual void update(float dt);

private:
    Vec3 position;
    Vec3 scaling;
    Vec3 eulerAngles;

    Mat4 localToWorld;
    bool isDirty;

    Vec3 color;
    
    const char *type;
    const size_t id;

    float movementSpeed;
    bool DOA;

    static std::unique_ptr<DirectX::Model> model;

    void build_transformation();

    void draw_mesh();
    virtual void draw_debug();
    static bool acquire_rendering_resources();
    static void release_rendering_resources();
    static void update_model(const Mat4 &view, const Mat4 &proj);



private:

    Agent_ROLE ag_Role = Agent_ROLE::NONE;
    const float radius = 5.f;

    Agent* targetAgent = nullptr;
    Agent* idealMatch = nullptr;

    int Appeal = 0;
    int Confidence = 0;
    int Fulfilment = 0;

};