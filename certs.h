#ifdef USE_CA_CERT
const char* root_ca_solar = \
                            "-----BEGIN CERTIFICATE-----" \
                            "MIII5TCCBs2gAwIBAgIQAOoDU1aKRUwxUYnjqgUSdDANBgkqhkiG9w0BAQwFADBE" \
                            "MQswCQYDVQQGEwJOTDEZMBcGA1UEChMQR0VBTlQgVmVyZW5pZ2luZzEaMBgGA1UE" \
                            "AxMRR0VBTlQgT1YgUlNBIENBIDQwHhcNMjEwNzE2MDAwMDAwWhcNMjIwNzE2MjM1" \
                            "OTU5WjBnMQswCQYDVQQGEwJHQjESMBAGA1UEBxMJU2hlZmZpZWxkMSAwHgYDVQQK" \
                            "ExdVbml2ZXJzaXR5IG9mIFNoZWZmaWVsZDEiMCAGA1UEAxMZd3d3LnNvbGFyLnNo" \
                            "ZWZmaWVsZC5hYy51azCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAKJ+" \
                            "4T6x4ZHnoz+twjjVKUG2AyoRBXR+HTk+204lCZ27PPvaC26OkH7f2bksQIMTaqjd" \
                            "Ug2ukpudW2Vwa/ANYs0YesnEpcDTt8N4b9WAH6uxQ6Bjr6Dao4yllgsH/nGQabLL" \
                            "NuFTAsVq8JRYLgeNREqnttXXcQhgzFmZraRjZZLxzwVkM/VrXEvSB8MLU8XT2hPu" \
                            "J2IzPkPMIJJlOioQt7BO9ivPDk9drxQMu7oau52AhHstICNWTyDW1vT6Jz+tSTkD" \
                            "Wiez8SqLv6lDHFVsmcP4D2LIPiIN0+ynh0xbzZswxLC61IQCMONY3GgOA5EKPh1S" \
                            "4DMi3XIOhydvFyc6vYMCAwEAAaOCBK4wggSqMB8GA1UdIwQYMBaAFG8dNUkQbDL6" \
                            "WaCevIroH5W+cXoMMB0GA1UdDgQWBBQ25gd0N1StK3KwITLFcrLhlpwHkjAOBgNV" \
                            "HQ8BAf8EBAMCBaAwDAYDVR0TAQH/BAIwADAdBgNVHSUEFjAUBggrBgEFBQcDAQYI" \
                            "KwYBBQUHAwIwSQYDVR0gBEIwQDA0BgsrBgEEAbIxAQICTzAlMCMGCCsGAQUFBwIB" \
                            "FhdodHRwczovL3NlY3RpZ28uY29tL0NQUzAIBgZngQwBAgIwPwYDVR0fBDgwNjA0" \
                            "oDKgMIYuaHR0cDovL0dFQU5ULmNybC5zZWN0aWdvLmNvbS9HRUFOVE9WUlNBQ0E0" \
                            "LmNybDB1BggrBgEFBQcBAQRpMGcwOgYIKwYBBQUHMAKGLmh0dHA6Ly9HRUFOVC5j" \
                            "cnQuc2VjdGlnby5jb20vR0VBTlRPVlJTQUNBNC5jcnQwKQYIKwYBBQUHMAGGHWh0" \
                            "dHA6Ly9HRUFOVC5vY3NwLnNlY3RpZ28uY29tMIIBfgYKKwYBBAHWeQIEAgSCAW4E" \
                            "ggFqAWgAdgBGpVXrdfqRIDC1oolp9PN9ESxBdL79SbiFq/L8cP5tRwAAAXquVQgS" \
                            "AAAEAwBHMEUCIF62sDZ35oUiGTQ4dBcfo35gMaG4f0NCEUpzJuFdDylfAiEAkkJY" \
                            "sCgkvJ2xJygLEiuUUj0yQWW21l+ygUSlZ9p8qsIAdgBByMqx3yJGShDGoToJQode" \
                            "TjGLGwPr60vHaPCQYpYG9gAAAXquVQfTAAAEAwBHMEUCIQDRdidwdf+Sy1T+rs5s" \
                            "vnHRJ/LfyGJDZAp+S195Awm7RwIgRWSWDViyaAG6y0knU4AwOwYu5oeNHN2h/nn8" \
                            "ldWod7oAdgApeb7wnjk5IfBWc59jpXflvld9nGAK+PlNXSZcJV3HhAAAAXquVQez" \
                            "AAAEAwBHMEUCIGzd9DxnHU9jwXIuZs38DJRwEEizIX4dzGAzNPfFFdkGAiEArxX6" \
                            "f7ehH2q0xbvw5A1I7MepRvSzZ1WlgzY8FYbrVfswggGkBgNVHREEggGbMIIBl4IZ" \
                            "d3d3LnNvbGFyLnNoZWZmaWVsZC5hYy51a4IUYXBpLnNvbGFyLnNoZWYuYWMudWuC" \
                            "GWFwaS5zb2xhci5zaGVmZmllbGQuYWMudWuCFWFwaTAuc29sYXIuc2hlZi5hYy51" \
                            "a4IaYXBpMC5zb2xhci5zaGVmZmllbGQuYWMudWuCHG1pY3JvZ2VuLWRhdGFiYXNl" \
                            "LnNoZWYuYWMudWuCIW1pY3JvZ2VuLWRhdGFiYXNlLnNoZWZmaWVsZC5hYy51a4Ib" \
                            "bWljcm9nZW4tc3RhZ2luZy5zaGVmLmFjLnVrgiBtaWNyb2dlbi1zdGFnaW5nLnNo" \
                            "ZWZmaWVsZC5hYy51a4IYc3RhZ2luZy5zb2xhci5zaGVmLmFjLnVrgh1zdGFnaW5n" \
                            "LnNvbGFyLnNoZWZmaWVsZC5hYy51a4Igd3d3Lm1pY3JvZ2VuLWRhdGFiYXNlLnNo" \
                            "ZWYuYWMudWuCJXd3dy5taWNyb2dlbi1kYXRhYmFzZS5zaGVmZmllbGQuYWMudWuC" \
                            "FHd3dy5zb2xhci5zaGVmLmFjLnVrMA0GCSqGSIb3DQEBDAUAA4ICAQCk5Bf8kr+3" \
                            "vVm3DUi1kkO877+3mZIPRYTK/GKaQSqBwKsQAwLQtS/Q2XZihGMeyLooBGXZow5H" \
                            "P36EpYKGqTZjIJg0qRswJKcBM01vgfPxYpVDQjqmD1BTlmHQdza8HXej1vk7GrFF" \
                            "2X9BDlsdUNHfWfp3Q/skwIQrNqBGVYt8UxppZvX5RMda/rGkxv0q14tgS9YKyNsT" \
                            "M8JXoLPZyaSiI9iBdgaXKxEhwuMjHidZC3ziVQXvGJjv/3ZFjpdeYVMGS/bTbOgs" \
                            "K4YPsYgBmpYO64qXWV3ErvAlnTDb9PtG6VDAfA6Qf6d4du+mBL7spcvF1Rs2l6JB" \
                            "cT3lxwPCtsdax+l92DkmRxSOnjLxmuRJkoigYdsgT9tNk3ZLEd8SHotQBjXB1NKG" \
                            "COLgPA+7lJC8D7TeA+Gv9TlppWXJ1JEEnUHtCHXJmXcDJP5PzLJkz2gfEsL1gIT4" \
                            "XgC5UXhngEpuyK1PmvC5zRovKltyBFgSWOOu4HkIbGNzP0htk9Sw6qm3tANn3s2g" \
                            "0Qu4vrJCA2qMTLgndltx1ITi3aIjO4/7J7gph76kcldtZkG+cynF5GE2eIhIpkaW" \
                            "56EvvVPSt6wG21GMn6LdNUlopXdWL4Zh/UdcvthlFg2B6EUjEYDgLUPVhQh+znMn" \
                            "V11aBB2AzPot8SrY3gqxvLofkH/ZhEOHgQ==" \
                            "-----END CERTIFICATE-----";

const char* root_ca_bmrs = \
                           "-----BEGIN CERTIFICATE-----" \
                           "MIIGZTCCBU2gAwIBAgIQB5cZQfNsmmhVinijW61zyjANBgkqhkiG9w0BAQsFADBe" \
                           "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3" \
                           "d3cuZGlnaWNlcnQuY29tMR0wGwYDVQQDExRHZW9UcnVzdCBSU0EgQ0EgMjAxODAe" \
                           "Fw0yMTExMjMwMDAwMDBaFw0yMjEyMjQyMzU5NTlaMFQxCzAJBgNVBAYTAkdCMQ8w" \
                           "DQYDVQQHEwZMb25kb24xGjAYBgNVBAoTEUNHSSBJVCBVSyBMSU1JVEVEMRgwFgYD" \
                           "VQQDDA8qLmJtcmVwb3J0cy5jb20wggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEK" \
                           "AoIBAQCsQqzpg1IVpPbjlMdQNsVwnQ1+oSrSyy9pRtYCfJ5BpAfrzD+Ix65+HOkI" \
                           "s9NJbwl4XUlRm7cZGYtF1Ecphec5RLwl5rGq5HNTvGPkxpNr4A1X5D8avUGy/5u8" \
                           "3fX6BCpd0jZ41weP6SIpMntdv00808ps47g/UzrzSL0xLb4Kg28hTvGYJzZimm0U" \
                           "j3jEU1aafVbCKer3xZ1hWhbFG+hOq+DRNNrjqU1NZ9jhiAcvfx7sIkDbIm+uX1x9" \
                           "rKZ2iBLBaVd6RcO8JZ/Wja13qJ8cuowNYNjKTjUnZ7Sgc3g/L2H6QBsuDhJeQsph" \
                           "6OgFEgLFG4PaUn3kY45O2WRHdVu/AgMBAAGjggMnMIIDIzAfBgNVHSMEGDAWgBSQ" \
                           "WP+wnHWoUVR3se3yo0MWOJ5sxTAdBgNVHQ4EFgQUqZkR9+pVGkZsKJCM8YrDnDo2" \
                           "8dQwKQYDVR0RBCIwIIIPKi5ibXJlcG9ydHMuY29tgg1ibXJlcG9ydHMuY29tMA4G" \
                           "A1UdDwEB/wQEAwIFoDAdBgNVHSUEFjAUBggrBgEFBQcDAQYIKwYBBQUHAwIwPgYD" \
                           "VR0fBDcwNTAzoDGgL4YtaHR0cDovL2NkcC5nZW90cnVzdC5jb20vR2VvVHJ1c3RS" \
                           "U0FDQTIwMTguY3JsMD4GA1UdIAQ3MDUwMwYGZ4EMAQICMCkwJwYIKwYBBQUHAgEW" \
                           "G2h0dHA6Ly93d3cuZGlnaWNlcnQuY29tL0NQUzB1BggrBgEFBQcBAQRpMGcwJgYI" \
                           "KwYBBQUHMAGGGmh0dHA6Ly9zdGF0dXMuZ2VvdHJ1c3QuY29tMD0GCCsGAQUFBzAC" \
                           "hjFodHRwOi8vY2FjZXJ0cy5nZW90cnVzdC5jb20vR2VvVHJ1c3RSU0FDQTIwMTgu" \
                           "Y3J0MAwGA1UdEwEB/wQCMAAwggGABgorBgEEAdZ5AgQCBIIBcASCAWwBagB3AEal" \
                           "Vet1+pEgMLWiiWn0830RLEF0vv1JuIWr8vxw/m1HAAABfUy4qtcAAAQDAEgwRgIh" \
                           "ALoG7+HiEL1pKUXfObFOoPjkrFedDrwMomyVWdNhZYItAiEA1HYnARMb9zDCpZ7f" \
                           "GqxCz+My6/YfDXC1jRo2REoTSPYAdwBRo7D1/QF5nFZtuDd4jwykeswbJ8v3nohC" \
                           "mg3+1IsF5QAAAX1MuKr0AAAEAwBIMEYCIQC8ljguYEV60HNHt4j+tFQLZwG4sHob" \
                           "scDQOrNf1JWnKAIhAMPCmud/tJsTk55HcYdeeIEGdBrnxoV46ack97NY/CoNAHYA" \
                           "QcjKsd8iRkoQxqE6CUKHXk4xixsD6+tLx2jwkGKWBvYAAAF9TLiqtwAABAMARzBF" \
                           "AiB7SWkkvbwJFqJHoRLfNBS/zwWfk7LVvDbFhwQtZDIZUAIhAJdaYk4uVndPU+0c" \
                           "bj0hQlnQPy1PFgzs4Ij9OA46ChRBMA0GCSqGSIb3DQEBCwUAA4IBAQBVSyze5Tha" \
                           "LceE+lxXtqMNf66UnRP1rFcgLPIYeNoSvoQ94DfaZHTSdA89bNAfzTy3M22ng7KK" \
                           "xN9OYYEF+ZVc3aEJJQV3w39aH52eqhpkUdEI5ghyt/uJHR9VPip+StSaCleU28F3" \
                           "WN8669RuZFkpG90MlApWDblOT1+jDvBimtkQF02VIrB9v4ZoEfRuWJYF1qhwxcIu" \
                           "wXgVazPaxFHUwZIoiif7AUNffwNEX6ZhHpPPeMw28O1Me7P5ayth3x7TR2MqltlV" \
                           "HZnWdFI1K/oTV7F8X9GWRyHlO3lkZ+BeYck1Z/IlEaVUtK46FieH6cDrJjxOVdft" \
                           "fBzvGHS53Arj" \
                           "-----END CERTIFICATE-----";
#else 
const char* root_ca_bmrs;
const char* root_ca_solar;
#endif
