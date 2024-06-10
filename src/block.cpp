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

//method to give a rectangle of the block's position to check for collisions
Rectangle Block::GetRect()
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 3;
    rect.height = 3;

    return rect;
}
