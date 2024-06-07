#include "block.hpp"


//set the position of the block
Block::Block(Vector2 position)
{
    this -> position = position;
}

//method to color the block yellow
void Block::Draw()
{
    DrawRectangle(position.x, position.y, 3, 3, {243, 216, 63, 255});
}