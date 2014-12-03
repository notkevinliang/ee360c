/*! Fragment Assembler implementation for EE360C Lab 3 */

#include "fragment_assembler.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <stdio.h>

fragment_assembler::fragment_assembler() {
    /* Nothing to do here */
}


auto fragment_assembler::add_fragment(fragment* fgmt) -> void {
    fragments.push_back(fgmt);
}

auto fragment_assembler::assemble(const std::string* desired_string)
    -> std::vector<std::vector<std::string> >* {

    fragment_package* pkg = new fragment_package();

    std::vector<std::vector<std::string> >* results_vec = 
        new std::vector<std::vector<std::string> >();

    std::vector<std::string> fragment_strings;

    std::vector<std::string> empty_vector;

    /* Shitty adapter */
    for (const auto fgmt : fragments) {
        fragment_strings.push_back(*(fgmt->to_string()));
    }

    poor_mans_bfs(*desired_string, &fragment_strings, empty_vector, results_vec);

    printf("%lu\n", results_vec->size());
    for (const auto strvec : *results_vec) {
        for (const auto str : strvec) {
            printf("%s ", str.c_str());
        }
        printf("\n");
    }

    /* for (const auto fgmt : fragments) { */
        /* bfs(desired_string, pkg); */
    /* } */

    return results_vec;
}

auto fragment_assembler::chop_assemble
    (const std::string* desired_string,
     const size_t begin_index,
     std::vector<fragment*>* recurrence_vector) -> bool {



    return false;
}

auto fragment_assembler::begins_with
(const std::string* desired, const std::string* fragment_string) -> size_t {

    if (desired->find(*fragment_string) == 0) {
        return fragment_string->size();
    } else {
        return 0;
    }
}


auto fragment_assembler::to_string() const -> const std::string {

    std::stringstream stb;

    for (const auto fgmt : fragments) {
        stb << fgmt->to_string() << "\n";
    }

    return stb.str();
}

auto fragment_assembler::poor_mans_bfs
    (std::string desired_string,
     std::vector<std::string>* fragment_strings,
     std::vector<std::string> current_strings,
     std::vector<std::vector<std::string> >* results) -> bool {

    if (desired_string.size() == 0) {

        /* DEBUG */
        printf("found: ");
        for (const auto str : current_strings) {
            printf("%s ", str.c_str());
        }
        printf("\n");
        /* END DEBUG */

        results->push_back(current_strings);

        return 1;
    }

    for (const auto str : *fragment_strings) {
        size_t chop = begins_with(&desired_string, &str);
        if (chop) {
            
            /* DEBUG */
            printf("chop: %s %lu %s: ", desired_string.c_str(), chop, str.c_str());
            for (const auto str : current_strings) {
                printf("%s ", str.c_str());
            }
            printf("\n");
            /* END DEBUG */

            current_strings.push_back(str);
            std::string substr = desired_string.substr(chop, desired_string.size());
            if (poor_mans_bfs(substr, fragment_strings, current_strings, results)) {

                /* DEBUG */
                printf("found, clearing: ");

                for (const auto str : current_strings) {
                    printf("%s ", str.c_str());
                }
                printf("\n");
                /* END DEBUG */
            }
            current_strings.pop_back();
        }
    }
    return 0;
}

auto fragment_assembler::bfs
    (const std::string* desired_string, fragment_package* pkg) -> void {

    /* Copy */
    std::vector<fragment*> possible_fragments = fragments;

    /* First pass */
    for (auto fgmt : possible_fragments) {
        if (desired_string->find(*(fgmt->to_string())) == 0) {
            pkg->push_trace(0, fgmt);
        }
    }

    std::cout << pkg->show_traces() << "\n";

    std::vector<fragment*> level;

    for (auto fgmt : *(pkg->get_current_traces())) {
        const auto adj_vec =
            pkg->get_adjacent_fragments(desired_string, possible_fragments, fgmt);

        for (auto adj_fgmt : adj_vec) {
            /* Don't know what to do here... */
            /* pkg-> */
        }
    }
}

auto print_recurrence_vector(std::vector<fragment*> recurrence_vector)
    -> const std::string {

    std::stringstream stb;

    for (const auto fgmt : recurrence_vector) {
        stb << fgmt->to_string()->c_str() << " ";
    }

    return stb.str();
}

auto fragment_assembler::check_assembly
(const std::string* desired_string,
 const std::vector<fragment*>* fragments) const -> bool {

    std::string concat = "";

    for (const auto fgmt : *fragments) {
        concat += *(fgmt->to_string());
    }

    if (desired_string->compare(concat) == 0) {
        return true;
    }
    return false;
}

auto fragment_assembler::reset_fragments() -> void {
    for (auto fgmt : fragments) {
        fgmt->reset();
    }
}
