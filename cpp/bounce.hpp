/**
 * @author  Michele Tomaiuolo - http://www.ce.unipr.it/people/tomamic
 * @license This software is free - http://www.gnu.org/licenses/gpl.html
 */

#ifndef BOUNCE_HPP
#define BOUNCE_HPP

#include "g2d/basic.hpp"
#include <set>
#include <string>
#include <typeinfo>
#include <vector>

using std::vector;
using std::string;
using namespace g2d;

class Ghost : public Actor {
private:
    Arena* arena_;
    int x_, y_;
    bool visible_ = true;
    static const int W = 20, H = 20, SPEED = 5;
public:
    Ghost(Arena* arena, Point position) {
        x_ = position.x; y_ = position.y;
        arena_ = arena;
        arena->add(this);
    }

    void move() {
        auto dx = g2d::randint(-1, 1) * SPEED;
        auto dy = g2d::randint(-1, 1) * SPEED;
        auto as = arena_->size();
        x_ = (x_ + dx + as.x) % as.x;
        y_ = (y_ + dy + as.y) % as.y;
        if (rand() % 100 == 0) {
            visible_ = !visible_;
        }
    }

    void collide(Actor* other) { }

    Point position() { return {x_, y_}; }

    Point size() { return {W, H}; }

    Point symbol() {
        if (visible_) return {20, 0};
        return {20, 20};
    }
};


class Ball : public Actor {
private:
    Arena* arena_;
    int x_, y_, dx_, dy_;
    static const int W = 20, H = 20, SPEED = 5;
public:
    Ball(Arena* arena, Point position) {
        x_ = position.x; y_ = position.y;
        dx_ = SPEED; dy_ = SPEED;
        arena_ = arena;
        arena->add(this);
    }

    void move() {
        auto as = arena_->size();
        if (!(0 <= x_ + dx_ &&  x_ + dx_<= as.x - W)) {
            dx_ = -dx_;
        }
        if (!(0 <= y_ + dy_ &&  y_ + dy_<= as.y - H)) {
            dy_ = -dy_;
        }
        x_ += dx_;
        y_ += dy_;
    }

    void collide(Actor* other) {
        if (typeid(*other) != typeid(Ghost)) {
            auto op = other->position();
            if (op.x < x_) {
                dx_ = SPEED;
            } else {
                dx_ = -SPEED;
            }
            if (op.y < y_) {
                dy_ = SPEED;
            } else {
                dy_ = -SPEED;
            }
        }
    }

    Point position() { return {x_, y_}; }

    Point size() { return {W, H}; }

    Point symbol() { return {0, 0}; }
};


class Turtle : public Actor {
private:
    Arena* arena_;
    int x_, y_, dx_, dy_;
    static const int W = 20, H = 20, SPEED = 2;
public:
    Turtle(Arena* arena, Point position) {
        x_ = position.x; y_ = position.y;
        dx_ = 0; dy_ = 0;
        arena_ = arena;
        arena->add(this);
    }

    void move() {
        auto as = arena_->size();
        x_ += dx_;
        if (x_ < 0) {
            x_ = 0;
        } else if (x_ > as.x - W) {
            x_ = as.x - W;
        }
        y_ += dy_;
        if (y_ < 0) {
            y_ = 0;
        } else if (y_ > as.y - H) {
            y_ = as.y - H;
        }
    }

    void collide(Actor* other) { }

    Point position() { return {x_, y_}; }

    Point size() { return {W, H}; }

    Point symbol() { return {0, 20}; }

    void control(std::set<string> keys) {
        string u="w", l="a", d="s", r="d";

        if (keys.count(u)) { dy_ = -SPEED; }
        else if (keys.count(d)) { dy_ = SPEED; }
        else dy_ = 0;

        if (keys.count(l)) { dx_ = -SPEED; }
        else if (keys.count(r)) { dx_ = SPEED; }
        else dx_ = 0;
    }
};

#endif // BOUNCE_HPP
