package g2d

type Actor interface {
    Move()
    Collide(other Actor)
    Position() Point
    Size() Point
    Symbol() Point
}

type Arena struct {
    w, h   int
    actors []Actor
}

func NewArena(size Point) *Arena {
    a := &Arena{size.X, size.Y, []Actor{}}
    return a
}

func (a *Arena) Add(actor Actor) {
    if !a.Contains(actor) {
        a.actors = append(a.actors, actor)
    }
}

func (a *Arena) Remove(actor Actor) {
    for i, v := range a.actors {
        if v == actor {
            a.actors = append(a.actors[:i], a.actors[i+1:]...)
            return
        }
    }
}

func (a *Arena) Contains(actor Actor) bool {
    for _, v := range a.actors {
        if v == actor {
            return true
        }
    }
    return false
}

func (a *Arena) MoveAll() {
    actors := a.ReversedActors()
    for _, actor := range actors {
        actor.Move()
        for _, other := range actors {
            if actor != other && a.CheckCollision(actor, other) {
                actor.Collide(other)
                other.Collide(actor)
            }
        }
    }
}

func (a *Arena) CheckCollision(a1, a2 Actor) bool {
    p1 := a1.Position()
    s1 := a1.Size()
    p2 := a2.Position()
    s2 := a2.Size()
    return (p2.X < p1.X+s1.X && p1.X < p2.X+s2.X &&
        p2.Y < p1.Y+s1.Y && p1.Y < p2.Y+s2.Y &&
        a.Contains(a1) && a.Contains(a2))
}

func (a *Arena) Actors() []Actor {
    actors := make([]Actor, len(a.actors))
    for i, v := range a.actors {
        actors[i] = v
    }
    return actors
}

func (a *Arena) ReversedActors() []Actor {
    actors := make([]Actor, len(a.actors))
    for i, v := range a.actors {
        actors[len(a.actors)-i-1] = v
    }
    return actors
}

func (a *Arena) Size() Point {
    return Point{a.w, a.h}
}
