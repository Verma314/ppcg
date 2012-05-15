#ifndef PPCG_H
#define PPCG_H

#include <isl/set.h>
#include <isl/union_set.h>
#include <isl/union_map.h>
#include <pet.h>

#include "ppcg_options.h"

int ppcg_extract_base_name(char *name, const char *input);

/* Representation of the scop for use inside PPCG.
 *
 * "options" are the options specified by the user.
 * Some fields in this structure may depend on some of the options.
 *
 * "start" and "end" are file offsets of the corresponding program text.
 * "context" represents constraints on the parameters.
 * "domain" is the union of all iteration domains.
 * "call" contains the iteration domains of statements with a call expression.
 * "reads" contains all read accesses.
 * "live_in" contains read accesses that have no corresponding
 *	writes in the scop.
 * "writes" contains all write accesses.
 * "kills" contains all kill accesses.
 * "dep_flow" represents the flow dependences.
 * "dep_false" represents the false (anti and output) dependences.
 * "schedule" represents the (original) schedule.
 *
 * "arrays" and "stmts" are copies of the corresponding elements
 * of the original pet_scop.
 */
struct ppcg_scop {
	struct ppcg_options *options;

	unsigned start;
	unsigned end;

	isl_set *context;
	isl_union_set *domain;
	isl_union_set *call;
	isl_union_map *reads;
	isl_union_map *live_in;
	isl_union_map *writes;
	isl_union_map *kills;
	isl_union_map *dep_flow;
	isl_union_map *dep_false;
	isl_union_map *schedule;

	int n_array;
	struct pet_array **arrays;
	int n_stmt;
	struct pet_stmt **stmts;
};

int ppcg_transform(isl_ctx *ctx, const char *input, FILE *out,
	struct ppcg_options *options,
	__isl_give isl_printer *(*fn)(__isl_take isl_printer *p,
		struct ppcg_scop *scop, void *user), void *user);

#endif
