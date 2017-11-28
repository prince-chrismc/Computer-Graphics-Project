#include "World.h"



World::World()
{
   auto chunk1 = std::make_shared<Chunk>();
   auto chunk2 = std::make_shared<Chunk>();
   auto chunk3 = std::make_shared<Chunk>();
   auto chunk4 = std::make_shared<Chunk>();
   auto chunk5 = std::make_shared<Chunk>();
   auto chunk6 = std::make_shared<Chunk>();
   auto chunk7 = std::make_shared<Chunk>();
   auto chunk8 = std::make_shared<Chunk>();
   auto chunk9 = std::make_shared<Chunk>();

   chunk1->Translate(glm::vec3(-Chunk::ONE_TRANS_UNIT, 0, -Chunk::ONE_TRANS_UNIT));
   chunk2->Translate(glm::vec3(-Chunk::ONE_TRANS_UNIT, 0, 0));
   chunk3->Translate(glm::vec3(-Chunk::ONE_TRANS_UNIT, 0, Chunk::ONE_TRANS_UNIT));

   chunk4->Translate(glm::vec3(0, 0, -Chunk::ONE_TRANS_UNIT));
   chunk5->Translate(glm::vec3(0, 0, 0));
   chunk6->Translate(glm::vec3(0, 0, Chunk::ONE_TRANS_UNIT));

   chunk7->Translate(glm::vec3(Chunk::ONE_TRANS_UNIT, 0, -Chunk::ONE_TRANS_UNIT));
   chunk8->Translate(glm::vec3(Chunk::ONE_TRANS_UNIT, 0, 0));
   chunk9->Translate(glm::vec3(Chunk::ONE_TRANS_UNIT, 0, Chunk::ONE_TRANS_UNIT));

   m_Map.emplace(Point{ -1, -1 }, chunk1);
   m_Map.emplace(Point{ -1, 0 }, chunk2);
   m_Map.emplace(Point{ -1, 1 }, chunk3);
   m_Map.emplace(Point{ 0, -1 }, chunk4);
   m_Map.emplace(Point{ 0, 0 }, chunk5);
   m_Map.emplace(Point{ 0, 1 }, chunk6);
   m_Map.emplace(Point{ 1, -1 }, chunk7);
   m_Map.emplace(Point{ 1, 0 }, chunk8);
   m_Map.emplace(Point{ 1, 1 }, chunk9);
}


World::~World()
{
}

bool World::HitsAnything(glm::vec3 cam_pos)
{
   if (cam_pos.x >= 0 && cam_pos.z >= 0)
   if(m_Map.at(Point{ 0, 0 })->TestForGround(std::floor(cam_pos.x), std::floor(cam_pos.z), cam_pos.y-1.0f)) return true;

   if(cam_pos.x >= 0 && cam_pos.y >= 0)
      return m_Map.at(Point{ 0, 0 })->TestForTree(std::floor(cam_pos.x), std::floor(cam_pos.z)) || m_Map.at(Point{ 0, 0 })->TestForTree(std::floor(cam_pos.x+1), std::floor(cam_pos.z)) || m_Map.at(Point{ 0, 0 })->TestForTree(std::floor(cam_pos.x + 2), std::floor(cam_pos.z));

    return false;
}
