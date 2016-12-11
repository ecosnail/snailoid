#include "game_state.hpp"
#include "collisions.hpp"

void GameState::update(float deltaSec)
{
    //if (_ballIsAttached) {
    //    return;
    //}

    Scalar minDistance = 1000000; // TODO: Support infinity in 2D space
    CircleCollision closestCollision = CircleCollision::none;
    for (const Block& block : _blocks) {
        CircleCollision collision = circleCollidesPolygon(
            _ball.geometry, _ball.velocity, block.geometry);
        if (collision.happened) {
            Scalar newDistance =
                distance(_ball.geometry.center(), collision.circleCenter);
            if (newDistance < minDistance) {
                minDistance = newDistance;
                closestCollision = collision;
            }
        }
    }

    if (closestCollision.happened) {
        float timeToCollision = minDistance / len(_ball.velocity);
        if (timeToCollision <= deltaSec) {
            _ball.velocity = mirrorAlong(
                _ball.velocity,
                closestCollision.collisionPoint -
                    closestCollision.circleCenter);
            _ball.geometry = Circle(
                closestCollision.circleCenter,
                _ball.geometry.radius());
        }
    } else {
        _ball.geometry = Circle(
            _ball.geometry.center() + _ball.velocity * deltaSec,
            _ball.geometry.radius());
    }





}