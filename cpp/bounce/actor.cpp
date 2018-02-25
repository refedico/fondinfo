#include "actor.h"

Arena::Arena(int width, int height) {
    w_ = width;
    h_ = height;
}

void Arena::add(Actor* a) {
    auto pos = find(begin(actors_), end(actors_), a);
    if (pos == actors_.end()) {
        actors_.push_back(a);
    }
}

void Arena::remove(Actor* a) {
    auto pos = find(begin(actors_), end(actors_), a);
    if (pos != actors_.end()) {
        actors_.erase(pos);
    }
}

void Arena::move_all() {
    auto acts = actors();
    reverse(begin(acts), end(acts));
    for (auto a : acts) {
        auto prev = a->rect();
        a->move();
        auto curr = a->rect();
        if (curr != prev) {
            for (auto other : acts) {
                if (other != a && check_collision(a, other)) {
                    a->collide(other);
                    other->collide(a);
                }
            }
        }
    }
}

bool Arena::check_collision(Actor* a1, Actor* a2) {
    auto r1 = a1->rect();
    auto r2 = a2->rect();
    return (r2[1] < r1[1] + r1[3] && r1[1] < r2[1] + r2[3]
        && r2[0] < r1[0] + r1[2] and r1[0] < r2[0] + r2[2]);
}

vector<Actor*> Arena::actors() { return actors_; }

vector<int> Arena::size() { return {w_, h_}; }

Arena::~Arena() {
    while (!actors_.empty()) {
        delete actors_.back();
        actors_.pop_back();
    }
}
