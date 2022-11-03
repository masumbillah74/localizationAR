/*
 * Copyright (c) 2019 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stddef.h>

#include "common_test.h"
#include <mbedtls/md.h>

/**@brief SHA test vectors can be found on NIST web pages.
 *
 * https://csrc.nist.gov/Projects/Cryptographic-Algorithm-Validation-Program/Secure-Hashing
 */
const char flash_data_sha_256[4096] = { "1234567890" };

/* SHA256 - Based on NIST CAVS 11.0 */
ITEM_REGISTER(test_vector_hash_256_data,
	      test_vector_hash_t test_vector_SHA256_invalid) = {
	.digest_type = MBEDTLS_MD_SHA256,
	.expected_err_code = 0,
	.expected_result = EXPECTED_TO_FAIL,
	.p_test_vector_name = TV_NAME("SHA256 invalid hash"),
	.p_input =
		"6a86b737eaea8ee976a0a24da63e7ed7eefad18a101c1211e2b3650c5187c2a8a65054"
		"7208251f6d4237e661c7bf4c77f335390394c37fa1a9f9be836ac28509",
	.p_expected_output =
		"42e61e174fbb3897d6dd6cef3dd2802fe67b331953b06114a65c772859dfc1aa"
};

/* SHA256 - NIST CAVS 11.0 */
ITEM_REGISTER(test_vector_hash_256_data,
	      test_vector_hash_t test_vector_SHA256_0) = {
	.digest_type = MBEDTLS_MD_SHA256,
	.expected_err_code = 0,
	.expected_result = EXPECTED_TO_PASS,
	.p_test_vector_name = TV_NAME("SHA256 message_len=0"),
	.p_input = "",
	.p_expected_output =
		"e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"
};

/* SHA256 - NIST CAVS 11.0 */
ITEM_REGISTER(test_vector_hash_256_data,
	      test_vector_hash_t test_vector_SHA256_4) = {
	.digest_type = MBEDTLS_MD_SHA256,
	.expected_err_code = 0,
	.expected_result = EXPECTED_TO_PASS,
	.p_test_vector_name = TV_NAME("SHA256 message_len=4"),
	.p_input = "c98c8e55",
	.p_expected_output =
		"7abc22c0ae5af26ce93dbb94433a0e0b2e119d014f8e7f65bd56c61ccccd9504"
};

/* SHA256 - NIST CAVS 11.0 */
ITEM_REGISTER(test_vector_hash_256_data,
	      test_vector_hash_t test_vector_SHA256_64) = {
	.digest_type = MBEDTLS_MD_SHA256,
	.expected_err_code = 0,
	.expected_result = EXPECTED_TO_PASS,
	.p_test_vector_name = TV_NAME("SHA256 message_len=64"),
	.p_input =
		"5a86b737eaea8ee976a0a24da63e7ed7eefad18a101c1211e2b3650c5187c2a8a65054"
		"7208251f6d4237e661c7bf4c77f335390394c37fa1a9f9be836ac28509",
	.p_expected_output =
		"42e61e174fbb3897d6dd6cef3dd2802fe67b331953b06114a65c772859dfc1aa"
};

/* SHA256 - NIST CAVS 11.0 */
ITEM_REGISTER(test_vector_hash_256_data,
	      test_vector_hash_t test_vector_SHA256_361) = {
	.digest_type = MBEDTLS_MD_SHA256,
	.expected_err_code = 0,
	.expected_result = EXPECTED_TO_PASS,
	.p_test_vector_name = TV_NAME("SHA256 message_len=361"),
	.p_input =
		"82829690aa3733c62b90d3297886952fc1dc473d67bb7d6bb299e088c65fc95ed3ca0f"
		"368d111d9fdcc9476cd4065efce7c481be598537f3f53bbbb6ff67973a69837454499e"
		"31398b463288e3aafb8b0600fdba1a25af806b83e1425f384e9eac7570f0c823981ba2"
		"cd3d868fba94648759623991e30f997c3bfb33d019150f0467a914f1eb79cd8727106d"
		"bf7d5310d0975943a6067cc79029b09239511417d922c7c7ac3dfdd8a41c52455b3c5e"
		"164b8289e141d820910f17a9668129743d936f7312e1604bc35f73ab164a3fddfe5fe1"
		"9b1a4a9f237f61cb8eb792e95d099a1455fb789d8d1622f6c5e976cef951737e36f7a9"
		"a4ad19ee0d068e53d9f60457d9148d5a3ce85a546b45c5c631d995f11f037e472fe4e8"
		"1fa7b9f2ac4068b5308858cd6d8586165c9bd6b322afa755408da9b90a87f3735a5f50"
		"eb8568daa58ee7cbc59abf8fd2a44e1eba72928816c890d1b0dbf6004208ff7381c697"
		"755adac0137cca342b1693",
	.p_expected_output =
		"5f4e16a72d6c9857da0ba009ccacd4f26d7f6bf6c1b78a2ed35e68fcb15b8e40"
};

/* SHA256 - NIST CAVS 11.0 */
ITEM_REGISTER(test_vector_hash_256_data,
	      test_vector_hash_t test_vector_SHA256_955) = {
	.digest_type = MBEDTLS_MD_SHA256,
	.expected_err_code = 0,
	.expected_result = EXPECTED_TO_PASS,
	.p_test_vector_name = TV_NAME("SHA256 message_len=955"),
	.p_input =
		"8390cf0be07661cc7669aac54ce09a37733a629d45f5d983ef201f9b2d13800e555d9b"
		"1097fec3b783d7a50dcb5e2b644b96a1e9463f177cf34906bf388f366db5c2deee04a3"
		"0e283f764a97c3b377a034fefc22c259214faa99babaff160ab0aaa7e2ccb0ce09c6b3"
		"2fe08cbc474694375aba703fadbfa31cf685b30a11c57f3cf4edd321e57d3ae6ebb113"
		"3c8260e75b9224fa47a2bb205249add2e2e62f817491482ae152322be0900355cdcc8d"
		"42a98f82e961a0dc6f537b7b410eff105f59673bfb787bf042aa071f7af68d944d2737"
		"1c64160fe9382772372516c230c1f45c0d6b6cca7f274b394da9402d3eafdf733994ec"
		"58ab22d71829a98399574d4b5908a447a5a681cb0dd50a31145311d92c22a16de1ead6"
		"6a5499f2dceb4cae694772ce90762ef8336afec653aa9b1a1c4820b221136dfce80dce"
		"2ba920d88a530c9410d0a4e0358a3a11052e58dd73b0b179ef8f56fe3b5a2d117a73a0"
		"c38a1392b6938e9782e0d86456ee4884e3c39d4d75813f13633bc79baa07c0d2d555af"
		"bf207f52b7dca126d015aa2b9873b3eb065e90b9b065a5373fe1fb1b20d594327d19fb"
		"a56cb81e7b6696605ffa56eba3c27a438697cc21b201fd7e09f18deea1b3ea2f0d1edc"
		"02df0e20396a145412cd6b13c32d2e605641c948b714aec30c0649dc44143511f35ab0"
		"fd5dd64c34d06fe86f3836dfe9edeb7f08cfc3bd40956826356242191f99f53473f32b"
		"0cc0cf9321d6c92a112e8db90b86ee9e87cc32d0343db01e32ce9eb782cb24efbbbeb4"
		"40fe929e8f2bf8dfb1550a3a2e742e8b455a3e5730e9e6a7a9824d17acc0f72a7f67ea"
		"e0f0970f8bde46dcdefaed3047cf807e7f00a42e5fd11d40f5e98533d7574425b7d2bc"
		"3b3845c443008b58980e768e464e17cc6f6b3939eee52f713963d07d8c4abf02448ef0"
		"b889c9671e2f8a436ddeeffcca7176e9bf9d1005ecd377f2fa67c23ed1f137e60bf460"
		"18a8bd613d038e883704fc26e798969df35ec7bbc6a4fe46d8910bd82fa3cded265d0a"
		"3b6d399e4251e4d8233daa21b5812fded6536198ff13aa5a1cd46a5b9a17a4ddc1d9f8"
		"5544d1d1cc16f3df858038c8e071a11a7e157a85a6a8dc47e88d75e7009a8b26fdb73f"
		"33a2a70f1e0c259f8f9533b9b8f9af9288b7274f21baeec78d396f8bacdcc22471207d"
		"9b4efccd3fedc5c5a2214ff5e51c553f35e21ae696fe51e8df733a8e06f50f419e599e"
		"9f9e4b37ce643fc810faaa47989771509d69a110ac916261427026369a21263ac4460f"
		"b4f708f8ae28599856db7cb6a43ac8e03d64a9609807e76c5f312b9d1863bfa304e895"
		"3647648b4f4ab0ed995e",
	.p_expected_output =
		"4109cdbec3240ad74cc6c37f39300f70fede16e21efc77f7865998714aad0b5e"
};

/* SHA256 - NIST CAVS 11.0 */
ITEM_REGISTER(test_vector_hash_256_data,
	      test_vector_hash_t test_vector_SHA256_1945) = {
	.digest_type = MBEDTLS_MD_SHA256,
	.expected_err_code = 0,
	.expected_result = EXPECTED_TO_PASS,
	.p_test_vector_name = TV_NAME("SHA256 message_len=1945"),
	.p_input =
		"eeb1a4c660be97e365dfe42a4d3400c6e661caaca02accd2ef41be9bf15b4c9651891a"
		"696bc60408b0ccaa2b4c2d2cfe079e321a699630b42218e814a9cc30492255f51c85df"
		"8042fdf7f8d68ea02806fba3830ce72665603a809c2bc64c27ff2bbc3dc6f73192f912"
		"08d5135ab67d448a17c5696003f53cff23e4c89202bb213267fb510ae3c295b8a64aca"
		"f796b2227ba3011b1d5468b238a6c7d35317731500fe37a4031d987eb7795de3ae6a4f"
		"0698ee3e0966424428afb44e3552b3d7445d28f7a72d099d1dd72a1846c757dd5aa7a1"
		"841b83f513082af37fd4d7fc7016108d4542cfcc58d8e06183db8a87e3857163db39bb"
		"945cb9720b6499291dc5f4e3d6285d3091511899c5a58b3e22e9efbedd4c4b5748a8a3"
		"4fa5056c923c5f449caba9e0997e1146cbff863c2d4f770056b6de399f387e2e886968"
		"365882c46f04b3ceb352bb1fc83eb72ed79d37162000979aebdb8d66c2e7fe97ddc416"
		"7edee397a1bfa3710308ba94a645d7024db78628864a536ee8c7320d9a4b1e2015f801"
		"ff2aead4c8466c073ef56c23d7a52dae10ad3c4f048da5323d7766aeca0f242591701d"
		"2ce76f5eec5e2336c8dea5ea41f814aa1676dcc4af373818bb3af6cc19f87b41f4f706"
		"45339c398a1041d5560687c57df1ed5e8d71a2e5488f985157a3da533c751f9489a29f"
		"3e4f4125bddac766c79b289199663f2784de700da92d8ce001f8f488a09102103a6fa4"
		"b4e6dc4a3c22ee038917b8e26e1fc1a7c185b69bb18c5bbc59b2c71a9635d18116d7c6"
		"58b2de5dc9fe60ec231ebddb7cdb6d599af6fc4f14bb5292b4da385d207318feb97004"
		"cfc417fa68c8df67133683e9814f5659bb43d6095a96834afbc8f232ee351d9c2e3afd"
		"6f96995b24511fe38293847aac8692d15e88893a7493c3bbacfc9461ac6174d747dd60"
		"37fc7d7d20bff8ff09fd9a49d5da8255a7bd0d57f70e929de63e50bace08a4e31ef780"
		"9965291889ac52deb00903b1c2712d51cdcee117195159e3540a3c55ebb61e40bbd846"
		"5be90bb53a0e96647d9841cc486d67abf3d14d060289b26a5740a778a62ba1a12ae9cd"
		"2d96ada3824f9ebea3d87eebf78d8a804c95a2ef1b12aa9a0d9a30e9bfeb4f9ac2dad3"
		"59e78d9d91b9ea4a814a4f0f923384e7e8d6eef137e60513d82a08e41c7defc9e01aa1"
		"5e61166717522ea0272cc3b7a0c62353dc250acd1d9569e770f865bbd75fa3f1a6d7c3"
		"352e862ae899f6051615b08aa9350d81dc934904f2bbd9832744fe0be7409bc73ed744"
		"c7902e97008a8ecf9458c2965418c01b838f8c65dd1b5ae7d8e9f3542a6859b48bfeae"
		"b8bcf9524ac8c84c698a6beb346f28ac447e805f3f956186aaf59dfeff009be100424d"
		"aa4aaf619a2d2bbc5bbb5024e41f6b3c9c31c7b6c2472fc40c4daecf8e18996cdef7cf"
		"8c768b40f259d9acebfa9ead3959e2f8506fd0e0c5ccc51c037fa7c9403678b3afa62b"
		"d0f72db60de5b6684d5dde7daf9755f010888690d29d7a56dbaff9f6e034f3b4e3b21f"
		"79fa7ae2265392722875f33b4dc8f482d5580748cdd6a37198e08125cf810b774bfc12"
		"447fc5bf5e0bd1ccea8f0ff307bd37a7b1b3c203e48739000423b3ea7c539a15a61cad"
		"cceb504b8a2b5fee6d5e70f6e77cb0a8b79bea76175759803777ba5cebcea412a05e1c"
		"6b95c4656c48d0151d2e736e8fa6deea1c30e818f1dab0a7cafc84c0fd25029aba557d"
		"48916da3d534e35c927fbaf5afb5b27d090dbc6f436db0921875421eefbf3320b065c4"
		"1fd7c47000c780da2760c905dfd3dcc3fcb5cc70bf5382dff94602957347f1358e4454"
		"3c27b39beebd26de91d61f66d89e266fa2d21a2ce5dcc50ce440b23ca936436daf98fe"
		"d7dfff287ebd2a95b4e49fbedfb094147c3a0f9464894d9c4e0661fd96311d513d9335"
		"8f30f3a2dccdcd45a4a300cdea79c7dadc92ea62ab30365599572a7c54d3f3a7827d9b"
		"079db97dd90143fc44432c7485c51f714987e91f5a4038027eaea3e79d2aeb1b217f81"
		"daa2fc480ac3c89b2a57769285c9d981abba1ac221eb07b5585eae04dcb82b2cceeabe"
		"39941021d0cf9918738da94901c1bb4e7cf08b090f2c333750469448c240f76f9e01f4"
		"f5d34c94d24bf3b27e7048a705efd5265abb4d64ed56c27c7f4c17133500b937ecaa8a"
		"8dcda11eac21d62ac466a13983a2c1a139f79eb63a78d03d843be524a1af5f70cf30fd"
		"765fd93c4e5b9a1c856b8a2712f97eb08b94da599992a7d8aafae6fae5a124e763924f"
		"a99cb3c8e81fa6b9f787eea915aa534eec1387a25eb3093981d34ad1e84d0f2b25fc16"
		"198b71fcd939e75ea154793f7b9393a95301a7974efe21135e879c9c14b856cab58fe1"
		"358ff31c928df5621f0a550142e348ee6cd078b744f44db802b26b9218c37cd918852f"
		"0dd29680ccbca23b459879bbf05065f87d25bac10a08ae4598486bd8c06e63f4a266e4"
		"7e1fdfec4b48f33ee3150bb5855bfdd96bf878b04e50a2d72dfeffd04bc3959e77c24e"
		"8f8ff09d5a47c6646927391678d3eb195f8fa36e2c02fb93753a58a8edf11fd2340f26"
		"ddf470692529e6ffb6c0824cb2640f77f395e01ef2facc49e7f8769d3283d2d3fa34e4"
		"68149ccb9526d9ff810c66d7b67a384ed1e306067e9ae88da43823e0dd3d432d29fa6b"
		"dde3aeead2f4ef0eed464b3dd47c3041f2e009e4bf9caabd412eee49d3169e3e25d195"
		"1b840b22045b11aecdfa859f5597557c1592ed51",
	.p_expected_output =
		"07ddd5dafcf04956cc36c1ff290f07c1c0e5832cc8dd9aea502da677ea04fe64"
};

/* SHA256 - NIST CAVS 11.0 */
ITEM_REGISTER(test_vector_hash_256_data,
	      test_vector_hash_t test_vector_SHA256_4123) = {
	.digest_type = MBEDTLS_MD_SHA256,
	.expected_err_code = 0,
	.expected_result = EXPECTED_TO_PASS,
	.p_test_vector_name = TV_NAME("SHA256 message_len=4123"),
	.p_input =
		"0f5452e6b51540cf219998590995cd7f8785fa40b4f217fc79f07322a2ec5e0834a426"
		"1a0177463779dfd958c33c55730dd3759f20167778372688c511967d584572c336d67f"
		"99f807c57c71704be39152222d8928a4d8307efef3a606ecd637e9c410825bb6a1da72"
		"526aec384ae1a2ff7a0948f425a2eef7829c0daa77d26dc8a4f545b9a3c6a5638e8911"
		"42c2b66ebbe3f123ad213c784ab96c4125bed9c18b195ac917cf71208182c227b73bca"
		"bd2f66cd617b1e10961eab498c9e4954fcda2b27549ec008147535fe78be3b8557020a"
		"854b85a685121b611c343da1a9e65ce3442f7500f549e6af234a804c4f04ddd80229f4"
		"4003b3eae2ce822c4d4247ba489aa2c6179e877df91ae625f5908b68d62a43ef75f240"
		"333645be90d585e79c630ff4b68b6d96e21acc94d4bfb0b54a0ee6e09fcbbb829d666b"
		"3094c2dc8ea83a8c6f6fe6c83dbc1a209cb530174a2c881f492cccc441d17927205d9b"
		"ae0389d8fa5919af1945b302fd45f1d22d12b54bbbc7bd007644777760d516e8630fe5"
		"423ffbdb6fc77770d94dd8b02d5bd48e5fa4a07aee395536690098e532637a6582459d"
		"dead3a999ba7f79d19c7075a5eccc01c8c1e763ab656eeb1f2ff150cb09ef2874af1da"
		"73dc75e3dc552a9b6ace9af9851b1893bca046126866dae38c6fa1300046c40fcfd94a"
		"f9dd8bde7dcd86d235214e65faa39c415404694834c44990e651faac41733d2e21e7e4"
		"69174b2d7c5e3a4e8c11b751509ccf22d3717ae775fcc38f33d828ae2943448855cfab"
		"6b9e5b16431542c0687ad20fba020077f057599c2de13cb6d444473a9e2a0fb7ea4214"
		"fd5489f48588c8de0d595d4a830d3fe724fb3dd5e5598615124f6e3e354f6f7139a96e"
		"8ecf5a40a811256db765e6348da522cf0c7de2f89514c2abc3ee452e5a116b4f7a6686"
		"ed196349b9b0e7223e3365ca1f47451aa0b087206808aa7286b7ccc2b11f12b3d4174a"
		"ebca9bcf6965c1ad19b6ef06a6884cb5902e74307e7f70b3d51ee59b89ff8b103426e1"
		"e665b220c53a1b6d8831b852e43b846f4a12216d0ecd1d34c8b2755efb4b57ebf4bc2c"
		"36f553d627936136ab5d48f261bed6759725d1377462d33e765458e520c116dcec858d"
		"7087efde0c3d68e000b2557182d43f0af20d319763bd628556e7141cc82bbc0f70f463"
		"5142f24c2b37cbd78c500da5a0d968fda3eb1a6ff834aab775fad9e4025ed6b962deb1"
		"53501e120ccee82ba0ba71eb8ea2de74c1d906d070ca7adf438dc394b7b8ea61c3783e"
		"f0bce05114768044ffac3a44b5a15155c108c34e2621d9259826fc6dece5ca1dceae69"
		"93b26f1bd90d1e1326c45788a8e447078095c80d0f49cdd57039016f4512ab12b7ebd5"
		"b3b87badd68b892ba587a3f43f18137f52060f76ecfa305f8e3e267b83c4a9ee6f6ab2"
		"212b7cec65d07a65d9121c8a8dd09452e7e813b946508e70e663c2d30478761b42b900"
		"d54c330a93bc2996e13bae407ae973c3bc00ddbf5ab45aba515df6641dd7291f2c29f3"
		"be93662b8d00d11592ef44321321d35c594aac12b30b4110bd1faa22e1d9443b1fce9f"
		"c10acf972c131ac0cf0ad008f5e2aa9730b5e8faee078b814d4fc4e531b4ac2e931435"
		"d41c4a6125f2b1b2e6d2e4e13d5fc8d3cfb9cdc8255270d654fd0596dd48b31dd20cc0"
		"2d3a420eadb718e6576645f5b10799943e5ed84df5d8c89af27289ef6cd725fbe7c868"
		"2caac1f27174da8a436bebb5e655f387ec0abbbafc29b6fdd10b2c8e85f5970b10924e"
		"860ca060d7bbe9c3364a75ae0957fe43fab2a4714d60e21970e6c16fd4c44ba4fc3f43"
		"c2d46313d7434906550396b7b9b144ca6b20a5d9e5f3a4b1186b4fbf0b7d92c5c62845"
		"d16e056a70b120af1f65063b026b1fa6d9da3e492f5977b9d4cd318e8e357b690cd1a4"
		"351b8a05ac1d8e221db63bf26dc83e7a5da2fca10a74313fba06d677d5aa49473270a8"
		"5d94987d2c754da14002905ace6672c7904b867ecf9e9673c293951c16ead5d2ce707a"
		"7b4dc82f66b16b177663ee0683ec84f2fd0bc3a4d204abb3923ae4b3d20047aaceada0"
		"c352eeb247da617cc8f85fbba0f619b09abce623eef5dba8736e9d2110be7384732c9f"
		"df06cdef991fed8ffa78b021eddef90f052d8b20bf7b6f4a079495c8fda7be6cf83e98"
		"35cb732b244861754c03da512959589e32b0359cb1ff1e99d392c5cefb07d6845c9d2d"
		"7bc7ae468bc179f48cd9255674390307bf7a149614bdcb3625f713b6d78c94b3a32032"
		"0c3ba9d79671c97311555c415b9e4d4be44cad30628b0625c6d9ec3a6e6bd6df9ccd2c"
		"a627caa14a708bc3f19803d0aef08acc4ab1c7d044eed4a516c69d92bade89716d0f5d"
		"08b35b5d979b26b4ae44a21541a08ca3fe78160edeb024fffbcdbab7a1b4b5f3a7b4ba"
		"1200c76d798d15e33735ba59e538c926d0c091ee5bba1f199ee3048353265875f325fe"
		"d51c162a9936d02181562540066273408e7776b8e18760e3e0472ca475482fc7c663f0"
		"8aae5b395c6dbe6ee49e0c1e456a1bd8a1fcba40dc349561a2a05945aba818c33d08ee"
		"99f384e5bbbed616ea29ec1187e1507faa74e8066f59df6d9031e301394c9137176f2d"
		"92b3d497c7fe737a202c80c71ec6356262fbd11bcd38e1dfe7f8be2f7ddc57d28ffe30"
		"c76983ab7e0f6f8748debda60b71b0133ac264430491a89bcc0a1033daa245da5042a0"
		"5a5fa7f7fdba09b74f4bfa332626923ce0bbc9f2ec4f24d98cad9430d8189b7e0785b0"
		"6dea07e5dbb98bc72f12c585e93f6a557eb8a01462e8b32c663409bb443a58f2785616"
		"bb526b319e4ae001e593e87bfef307a722d1d2543490f60aec1b7b4034c14acfd244ed"
		"a7482c97c0f86164548cf9e14c954fcff872552402742b53a540f0cd1a74d8c8538d7e"
		"3fec087c3a5fc73a4f77b7036907b05ec8db9c9b49efdcace8dfe736839f34e8e16c5b"
		"0cf202775b5810ce1627e9b452e97cac94e686d19da2067487a6f207118328393815a7"
		"630705ff23af910646da90cdec3db0d2e66c037763f3bab3cca23008ec282ab554e45d"
		"2cfef730c6309ec4b6a3bf313ce5c1131bfca1464c4c42edf4bb05b994129a687fa616"
		"8b9239458d1f1b41f12a9443dbd887bad2244f9ac4d4edf74aab65d22ee165332bd028"
		"78f3f09aec7705bd9b62974b65e6a39d52bc90cb2566641534b838817696eac6deff11"
		"69e74b362671b04191cb0b31fd11dd109db89426e9670d6e43085646db20b86ad05bf5"
		"23986ccebca113c836387f303dabd75d5aaa143569f311f34e2fe527e41670fd36da34"
		"c3f2c366a61a1645bcfd3cab486620e23913d9b8f36889d65265854decd6b67297c93f"
		"ec2c455f0b8a39995cddb3137a20523d26e0feb29a43d6631b4a6af2ce532b5ccce220"
		"db78a0da0b11a4a94b83f2106683417773da0220f9019d5c57effeff632f5011523508"
		"c6d8f226b08fa6b7349df69f3b923e95298f286f13ad7ea02d9c3cff818beacae74828"
		"ea31a98b78a62aa781b2d76d06db6db847f7bc22429c4f1c76d94f3eec23a5db78925f"
		"d93d4e55bf6f440c105d1ddad8ae704b84ea36c4f63d7f66d978643532593d7a380c14"
		"6666f159f7cea0d620b02be6244ba3e243f3dddd9864759142561498c252efe0a4c390"
		"596250d9f0856946c10d207288133bdd59ad87ec92126f310dfecced9a58ffd3ac133e"
		"0f52522b8769cfab61117df5c55d6ce9e44feda43903f8510e2aca4143bad23f4be4ce"
		"1d774732937763c94a1e509e3365af1d1db3e276875b7842b266eb69fb948e43689dc1"
		"fd81bc673f616e9a0b0c789de90327114116db6c087ac7a89e1bf238f7338140fa1c39"
		"05266340a37b1d23fe987e1dfa21a797ef63c0eb573b476dca33a7ac2def0df526c877"
		"19d2b60e70bb73b51e04dde295e79dac5c6206260e2c3feca5eea5fbf8b06bc6839183"
		"8667bcc2d1b1973f6edf3efc68a12fc861dc476329f4ede48f4b8d58770548ac2d0fe9"
		"cdf95f1b0df47ddac9194228489fdf01e78722907371f5a3d7b3285df7ac702adb56af"
		"f8101b75a54beac7b350892043122db6411c48fedc2fa272392dab926835102997108c"
		"d185cc01b93aa6c7a6f62e433867a5bc6f1eaa6b6d4416d17e89244e555ed5ee996492"
		"86a02413007a0081f33169d7774f538e37a1e679c73b77ee38bcb626ead329e6a202d9"
		"5fdca24b546328b17a1ea662242d95881f35d118dbf7e508cc2889bc107c69c1520528"
		"bdeebba5a6565c7d33b476d190d1c1495635b358ba904fc205583e5c44b42013409924"
		"30b032d6dbae8639dd685516aa1842939e36380787eb060d64ca4cd86cbb9bc65237d8"
		"37c8bbe19f427673dafc454cc03ee28cfadf59611408bbe3d23a153dc892a30e254c42"
		"0fd08724f5b647c79962c02856ced234b278d07f41b98538c752795d9d48702b56f334"
		"d9a151948571a0ad6f5c2b68654164447e2e33560b818e8ecb4d4a3b5eff30d1fc4154"
		"ea671ea28c1e67baaad456feed2072e8b476b2a25956e5d0b6c351b0e7f79b665255e7"
		"91e59f3f229f69396e52ced482a761a4b662662f85e743969bfd317830d33713954159"
		"ac0c4f0d31ddfbee1ea637b49df33264f10ed8c414199c129f5975f5ebd526b47620c3"
		"a6887371ea16fe6d57e68050b6f416912f15504b02da8a4078b77a1f186405021d8457"
		"3b2885325033c78644c60043186ddf6b9269ef6b3da6bfabb1ed4064145b6eb2e11232"
		"eae82e872d97fbdd3d7765ba90f9afa7a373684a91669bd0e402478eabec0ee7cd3e31"
		"709cd0bc52adb6fef0e8093ccadbeba7a153c58add2ed3c82b6be3866a835925c8fc77"
		"73283bdb22c89a497920baab490d1b56232ee98fc88e194ee184b542f0d8741487278e"
		"f0b889ce42cc70e9bd37d40ea2cc8dbe3f2e00deb687fd0bff7ce82d3060174ffca77c"
		"ae7a9e840f285a3e5630eec055eae2c7e2a1e09d2c9aaf404f5266c02508d9e95f7b58"
		"22d5f599951b88f2905598cb2b4c9a542cc11a7327010301eab91b35180ccd6013e32b"
		"db1f84333ec56751d37644264b717188afe76bca995cb33da350dbf6201fe0d20a26ba"
		"b83c27321ee1eef4cf2d35e5eb4bc6b62f96dfba760bdaf480fe0d75f30df0e59f537d"
		"5f06dedd821c6240c44b2e0d0aba603b76cf55fe80f364a74995ccc52b71ea919512b0"
		"891695525ab7b142038ef45f38904f6a04a7d5b9b305c02fefb7b56b297d49403bd9c3"
		"654b66236ef26b64fb9db0ff303490b065fa507c1eb5aff33d0ebeb3763af22d04da78"
		"ac9a20c8939d347de590d6640bd044d3d2815e3cb4c80801583ad08a5c95d19651aed6"
		"ce07abc3a00b72314a6f625935c94033857e74dfee417543c9d682f6671c935ca54a8f"
		"13c079bf8e6b6383001f6a437cb3dca95a2c750ddcd625311294142ffa74e4afec8636"
		"5d35ef6f9b0339bc7281ed53cf4264fcece3dad00cecc4416bf8635b75169a4a366efd"
		"1b12282ac7b6895c6d4e5f3ddff8a0fc60794ea0ac309d9c394858a3bd3181bdf05038"
		"9b93f5dd27b18e7960251b5a655ce2fecf5c643344058f7b4a9735b55875bdfa332919"
		"c678a7f85874d63c5b3c4caec5fa59f0008648b44836e12c54f633c1389b90088a74d8"
		"f2c322fb43e9aab9456bc9acbd4d88891e840fa3fda4beb0c5b87ad0ac7145cbe58412"
		"9a174dd72a0fb8e35cb261725035fa7fe390eed9762f4379f2ebc513083a61ebbea2cf"
		"ea277474f171b6866d2661712cabcd796f0d69a140fcafcc05185723566ccbb60c38dc"
		"669af4b302a1910ab0be029c8fa7fbd99a76f9dfd04482a692faae7a",
	.p_expected_output =
		"f98918c63e3a9238e78dbd5bebe4e47eaeec0ae1627387dcd2a5ae4725f7e47c"
};

ITEM_REGISTER(test_vector_hash_256_long_data,
	      test_vector_hash_t test_vector_SHA256_long) = {
	.digest_type = MBEDTLS_MD_SHA256,
	.expected_err_code = 0,
	.expected_result = EXPECTED_TO_PASS,
	.mode = NO_MODE,
	.chunk_length = 4096,
	.update_iterations = 256,
	.p_test_vector_name = TV_NAME("SHA256 message_len=1048576"),
	.p_input = flash_data_sha_256,
	.p_expected_output =
		"7b09661bdd3dc086e9303102e0c1da76eef506e403419f722947e377a6edec00"
};

ITEM_REGISTER(test_vector_hash_256_long_data,
	      test_vector_hash_t test_vector_SHA256_long_flash) = {
	.digest_type = MBEDTLS_MD_SHA256,
	.expected_err_code = 0,
	.expected_result = EXPECTED_TO_PASS,
	.mode = DO_MEMCPY,
	.chunk_length = 4096,
	.update_iterations = 256,
	.p_test_vector_name = TV_NAME("SHA256 flash memcpy message_len=1048576"),
	.p_input = flash_data_sha_256,
	.p_expected_output =
		"7b09661bdd3dc086e9303102e0c1da76eef506e403419f722947e377a6edec00"
};
