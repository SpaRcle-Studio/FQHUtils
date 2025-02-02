/**
 * Author:    Andrea Casalino
 * Created:   03.12.2019
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#ifndef HULL_HULL_H
#define HULL_HULL_H

#include <Hull/Coordinate.h>
#include <cmath>
#include <memory>
#include <vector>

namespace hull {
    struct Facet {
      std::size_t vertexA;
      std::size_t vertexB;
      std::size_t vertexC;

      Facet *neighbourAB = nullptr;
      Facet *neighbourBC = nullptr;
      Facet *neighbourCA = nullptr;

      Coordinate normal; // outer normal
    };
    using FacetPtr = std::unique_ptr<Facet>;

    using Facets = std::vector<FacetPtr>;
    using RemovedFacets = std::vector<std::unique_ptr<const Facet>>;

    struct HullContext {
      std::vector<Coordinate> vertices;
      std::vector<FacetPtr> faces;
    };

    class Observer {
    public:
      virtual ~Observer() = default;

      struct Notification {
        std::vector<const Facet *> changed;

        std::vector<const Facet *> added;
        RemovedFacets removed;

        const HullContext &context;
      };

      virtual void hullChanges(Notification &&notification) = 0;
    };

    class Hull {
    public:
      Hull(const Coordinate &A, const Coordinate &B, const Coordinate &C,
           const Coordinate &D);

      Hull(const Coordinate &A, const Coordinate &B, const Coordinate &C,
           const Coordinate &D, Observer &obs);

      void setObserver(Observer &obs);

      void update(const Coordinate &vertex_of_new_cone);

      void update(const Coordinate &vertex_of_new_cone,
                  const std::size_t starting_facet_for_expansion);

      const std::vector<Coordinate> &getVertices() const {
        return vertices_and_faces.vertices;
      };
      const Facets &getFacets() const { return vertices_and_faces.faces; };

    private:
      void initThetraedron(const Coordinate &A, const Coordinate &B,
                           const Coordinate &C, const Coordinate &D);

      void update_(const Coordinate &vertex_of_new_cone,
                   const std::size_t starting_facet_for_expansion);

      void recomputeNormal(Facet &subject) const;

      FacetPtr makeFacet(const std::size_t vertexA, const std::size_t vertexB,
                         const std::size_t vertexC) const;

      struct VisibleCone;
      VisibleCone computeVisibleCone(const Coordinate &vertex_of_new_cone,
                                     const std::size_t starting_facet);

      HullContext vertices_and_faces;
      Coordinate Mid_point;

      Observer *observer = nullptr;
    };
} // namespace hull

#endif //HULL_HULL_H