# first_repo
https://docs.google.com/document/d/1PVhW_l2opK4U9VCW4C0e3qiU4m6thlXHGjRGBe02BsU/edit?usp=sharing


sudo perf stat --repeat=10 --table -e instructions,L1-dcache-loads,L1-dcache-load-misses,l2_cache_req_stat.ic_access_in_l2,l2_cache_req_stat.ic_dc_miss_in_l2,branch-instructions,branch-misses ./heat_sim_bad>/dev/null
