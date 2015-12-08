#ifndef DECON_HPP
#define DECON_HPP
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <stack>
#include "Variant.h"
#include "index.hpp"
#include "path.hpp"
#include "vg.hpp"
#include "vg.pb.h"
#include "Fasta.h"
#include "xg.hpp"
#include "position.hpp"


namespace vg{
    using namespace std;
    class Deconstructor{
        public:

            Deconstructor();
            ~Deconstructor();
            void clear();
            void set_xg(string xg);
            void enumerate_path_names_in_index();
            void set_reference(string ref_file);
            void set_index(string index_file);
            void set_graph(VG* v);

            /**
             * Project a path onto another path,
             * much like a projection of p2 onto p1 in space.
             */
             //list<Mapping> relative_mapping(Path& p1, Path& p2);

             void print_using_edges(string pathname);

            vector<int64_t> get_variant_node_ids(string pathname);
            //vector<Mapping> get_mappings_for_variant(int64_t variant_node_id);

            // bool surject_alignment(Alignment& source,
            //                         set<string> path_names,
            //                         Alignment& surjection,
            //                         string& path_name,
            //                         int64_t& path_pos,
            //                         int window);

            vector<vcflib::Variant> get_variants(string region_file);
            /**
            *
            */
            vector<vcflib::Variant> get_variants(string region_name, int start, int end);

            /**
             * Build a vcf record from a mapping.
             */
            vcflib::Variant mapping_to_simple_variant(Mapping m, int64_t alt_id);

            list<Mapping> get_mappings_off_reference(Path& ref);
            list<Mapping> get_mappings_off_reference(string pathname);

            Mapping node_id_to_mapping(int64_t node_id);
            /**
             * Turn a vector of variants into a proper VCF.
             */
            void write_variants(string filename, vector<vcflib::Variant> variants);

        private:
            // TODO Should be able to handle XG or VG indices
            string index_file;
            string reference;
            string xg_file;
            VG* vgraph;
            vector<string> ref_paths;
            map<string, int64_t> inter_ref_and_index;

    };
}
#endif
