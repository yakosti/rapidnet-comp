#./scripts/bash_scripts/storage_rate_cdf_dns.sh dns-prov-dhlist-layerhs-online-test 7 /localdrive1/harshal/dns/storage_rate_cdf/dns_storage_online_large.txt /localdrive1/harshal/dns/storage_rate_cdf/dns_storage_online 2 10000
#./scripts/bash_scripts/storage_rate_cdf_dns.sh dns-prov-dist-hlist-rmitm-test 7 /localdrive1/harshal/dns/storage_rate_cdf/dns_storage_rmitm_large.txt /localdrive1/harshal/dns/storage_rate_cdf/dns_storage_rmitm 2 10000
#./scripts/bash_scripts/storage_rate_cdf_dns.sh dns-prov-test 7 /localdrive1/harshal/dns/storage_rate_cdf/dns_storage_nocomp_large.txt /localdrive1/harshal/dns/storage_rate_cdf/dns_storage_nocomp 2 10000
nohup ./waf --run "dns-prov-dhlist-layerhs-online-test --storePth=/localdrive1/harshal/dns/storage_cdf/dns_storage_online/ --numNodes=100 --numRequests=100000"
nohup ./waf --run "dns-prov-dist-hlist-rmitm-test --storePth=/localdrive1/harshal/dns/storage_cdf/dns_storage_rmitm/ --numNodes=100 --numRequests=100000"
nohup ./waf --run "dns-prov-test --storePth=/localdrive1/harshal/dns/storage_cdf/dns_storage_nocomp/ --numNodes=100 --numRequests=100000"
