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

void World::Update(glm::vec3 cam_pos)
{
   static std::once_flag blockTL;
   if (cam_pos.x > 64.0f && cam_pos.z > 64.0f)
   {
      std::call_once(blockTL, [this]{
         auto chunk7 = std::make_shared<Chunk>();
         auto chunk8 = std::make_shared<Chunk>();
         auto chunk9 = std::make_shared<Chunk>();

         chunk7->Translate(glm::vec3(2*Chunk::ONE_TRANS_UNIT, 0, Chunk::ONE_TRANS_UNIT));
         chunk8->Translate(glm::vec3(2 * Chunk::ONE_TRANS_UNIT, 0, 2*Chunk::ONE_TRANS_UNIT));
         chunk9->Translate( glm::vec3(Chunk::ONE_TRANS_UNIT, 0, 2*Chunk::ONE_TRANS_UNIT));

         m_Map.emplace(Point{2, 1}, chunk7);
         m_Map.emplace(Point{ 2, 2 }, chunk8);
         m_Map.emplace(Point{ 1, 2 }, chunk9);
      });
   }

}
