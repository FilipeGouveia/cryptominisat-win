/******************************************
Copyright (C) 2009-2020 Authors of CryptoMiniSat, see AUTHORS file

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
***********************************************/

#include "cl_predictors_abs.h"
#include "solver.h"

using namespace CMSat;

extern const char* predictor_short_json_hash;
extern const char* predictor_long_json_hash;
extern const char* predictor_forever_json_hash;

vector<std::string> ClPredictorsAbst::get_hashes() const
{
    vector<std::string> ret;
    ret.push_back(string(predictor_short_json_hash));
    ret.push_back(string(predictor_long_json_hash));
    ret.push_back(string(predictor_forever_json_hash));

    return ret;
}

int ClPredictorsAbst::set_up_input(
    const CMSat::Clause* const cl,
    const uint64_t sumConflicts,
    const double   act_ranking_rel,
    const double   uip1_ranking_rel,
    const double   prop_ranking_rel,
    const double   sum_uip1_per_time_ranking,
    const double   sum_props_per_time_ranking,
    const double   sum_uip1_per_time_ranking_rel,
    const double   sum_props_per_time_ranking_rel,
    const ReduceCommonData& commdata,
    const Solver* solver,
    float* at)
{
    uint32_t x = 0;
    //glue 0 can happen in case it's a ternary resolvent clause
    //updated glue can actually be 1. Original glue cannot.
    const ClauseStatsExtra& extra_stats = solver->red_stats_extra[cl->stats.extra_pos];
    assert(extra_stats.orig_glue != 1);

    assert(cl->stats.last_touched <= sumConflicts);
    assert(extra_stats.introduced_at_conflict <= sumConflicts);
    uint32_t last_touched_diff = sumConflicts - (uint64_t)cl->stats.last_touched;
    double time_inside_solver = sumConflicts - (uint64_t)extra_stats.introduced_at_conflict;

    at[x++] = sum_props_per_time_ranking;
//     rdb0.sum_props_per_time_ranking
    at[x++] = act_ranking_rel;
//     rdb0.act_ranking_rel
    at[x++] = commdata.avg_props;
//     rdb0_common.avg_props
    at[x++] = extra_stats.discounted_props_made3;
//     rdb0.discounted_props_made3
    at[x++] = solver->hist.glueHistLT.avg();
//     rdb0_common.glueHistLT_avg

    if (time_inside_solver  == 0) {
        at[x++] = missing_val;
    } else {
        at[x++] = (double)extra_stats.sum_props_made/time_inside_solver;
    }
    //(rdb0.sum_props_made/cl.time_inside_solver) -- 6

    at[x++] = uip1_ranking_rel;
//     rdb0.uip1_ranking_rel

    if (commdata.avg_props == 0) {
        at[x++] = missing_val;
    } else {
        at[x++] = (double)cl->stats.props_made/(double)commdata.avg_props;
    }
    //(rdb0.props_made/rdb0_common.avg_props) -- 8

    at[x++] = extra_stats.discounted_props_made;
//     rdb0.discounted_props_made
    at[x++] = sum_uip1_per_time_ranking_rel;
//     rdb0.sum_uip1_per_time_ranking_rel
    at[x++] = commdata.avg_uip;
//     rdb0_common.avg_uip1_used
    at[x++] = prop_ranking_rel;
//     rdb0.prop_ranking_rel
    at[x++] = sum_props_per_time_ranking_rel;
//     rdb0.sum_props_per_time_ranking_rel

    //To protect against unset values being used
    assert(cl->stats.is_ternary_resolvent ||
        extra_stats.glueHist_longterm_avg > 0.9f);

    if (cl->stats.is_ternary_resolvent ||
        extra_stats.glue_before_minim == 0 //glueHist_longterm_avg does not exist for ternary
    ) {
        at[x++] = missing_val;
    } else {
        at[x++] = (double)extra_stats.glueHist_longterm_avg/(double)extra_stats.glue_before_minim;
    }
    //(cl.glueHist_longterm_avg/cl.glue_before_minim) -- 14

    at[x++] = extra_stats.discounted_uip1_used3;
//     rdb0.discounted_uip1_used3
    at[x++] = extra_stats.discounted_props_made2;
//     rdb0.discounted_props_made2
    at[x++] = cl->stats.props_made;
//     rdb0.props_made
    at[x++] = extra_stats.discounted_uip1_used;
//     rdb0.discounted_uip1_used
    at[x++] = extra_stats.discounted_uip1_used2;
//     rdb0.discounted_uip1_used2
    at[x++] = cl->stats.uip1_used;
//     rdb0.uip1_used

    assert(x==PRED_COLS);
    return PRED_COLS;
}
