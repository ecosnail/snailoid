#include "game_state.hpp"
#include "collisions.hpp"

namespace game {

State::State()
    : ball()
    , blocks()
{
    blocks.emplace_back(0.1f, 0.8f, 0.1f, 0.05f);
}

void State::update(float deltaSec)
{
    //if (_ballIsAttached) {
    //    return;
    //}

    
    game::Coord minDistance = 1000000; // TODO: Support infinity in 2D space
    CircleCollision closestCollision = CircleCollision::none;
    for (const Block& block : blocks) {
        CircleCollision collision = circleCollidesPolygon(
            ball.geometry, ball.velocity, block.geometry);
        if (collision.happened) {
            game::Coord newDistance =
                distance(ball.geometry.center(), collision.circleCenter);
            if (newDistance < minDistance) {
                minDistance = newDistance;
                closestCollision = collision;
            }
        }
    }

    if (closestCollision.happened) {
        float timeToCollision = minDistance / len(ball.velocity);
        if (timeToCollision <= deltaSec) {
            ball.velocity = mirrorAlong(
                ball.velocity,
                closestCollision.collisionPoint -
                    closestCollision.circleCenter);
            ball.geometry = Circle(
                closestCollision.circleCenter,
                ball.geometry.radius());
        }
    } else {
        ball.geometry = Circle(
            ball.geometry.center() + ball.velocity * deltaSec,
            ball.geometry.radius());
    }


}

} // namespace game