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

bool World::HitsAnything(glm::vec3 cam_pos, glm::vec3 cam_front)
{
   //int x_val = std::floor(cam_pos.x);
   //   int y_val = std::floor(cam_pos.z);
   Point chunk_to_check{0,0};
   //chunk_to_check.x = (x_val % 128.0f);
   //chunk_to_check.y = (y_val % 128.0f);
   //if (cam_pos.x < 0) chunk_to_check.x = -chunk_to_check.x;
   //if(cam_pos.z < 0) chunk_to_check.y = -chunk_to_check.y;
   if (cam_pos.x < 0.0f && cam_pos.x > -128.0f) chunk_to_check.x = -1;
   if (cam_pos.x > 0.0f && cam_pos.x < 128.0f) chunk_to_check.x = 0;
   if (cam_pos.x > 128.0f && cam_pos.x < 256) chunk_to_check.x = 1;
   if (cam_pos.z < 0.0f && cam_pos.z > -128.0f) chunk_to_check.y = -1;
   if (cam_pos.z > 0.0f && cam_pos.z < 128.0f) chunk_to_check.y = 0;
   if (cam_pos.z > 128.0f && cam_pos.z < 256) chunk_to_check.y = 1;

      if(m_Map.at(chunk_to_check)->TestForGround(std::floor(std::abs(cam_pos.x)), std::floor(std::abs(cam_pos.z)), cam_pos.y-0.5f)) return true;


      if(std::abs(cam_front.x) > std::abs(cam_front.z)){
      int check_x = (cam_front.x > 0) ? 1 : -1;

      return m_Map.at(chunk_to_check)->TestForTree(std::abs((int)std::floor(cam_pos.x)%128), std::floor(cam_pos.z)) || 
             m_Map.at(chunk_to_check)->TestForTree(std::abs((int)std::floor(cam_pos.x + 1*check_x)%128), std::abs(std::floor(cam_pos.z))) || 
             m_Map.at(chunk_to_check)->TestForTree(std::abs((int)std::floor(cam_pos.x + 2*check_x)%128), std::abs(std::floor(cam_pos.z))) ||
             m_Map.at(chunk_to_check)->TestForTree(std::abs((int)std::floor(cam_pos.x + 2*check_x)%128), std::abs(std::floor(cam_pos.z + 1))) ||
             m_Map.at(chunk_to_check)->TestForTree(std::abs((int)std::floor(cam_pos.x + 2*check_x)%128), std::abs(std::floor(cam_pos.z + 1))) ||
             m_Map.at(chunk_to_check)->TestForTree(std::abs((int)std::floor(cam_pos.x + 3*check_x)%128), std::abs(std::floor(cam_pos.z))) ||
             m_Map.at(chunk_to_check)->TestForTree(std::abs((int)std::floor(cam_pos.x + 3*check_x)%128), std::abs(std::floor(cam_pos.z+1))) ||
             m_Map.at(chunk_to_check)->TestForTree(std::abs((int)std::floor(cam_pos.x + 3*check_x)%128), std::abs(std::floor(cam_pos.z+1)));
             }

      if (std::abs(cam_front.x) < std::abs(cam_front.z)) {
         int check_x = (cam_front.z > 0) ? 1 : -1;

         return 

    return false;
}
