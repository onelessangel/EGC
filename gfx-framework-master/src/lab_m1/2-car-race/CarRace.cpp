#include "lab_m1/2-car-race/CarRace.hpp"

using namespace gfxc;
using namespace std;
using namespace m1;
using namespace transform3D;
//using namespace objects;

CarRace::CarRace()
{

}

CarRace::~CarRace()
{

}

void CarRace::Init()
{
	renderCameraTarget = false;
	onTrack = true;

	// set initial position and angle
	playerCenter = glm::vec3(-26.8, .15, 5);
	playerAngle = -M_PI_2 + .1;

	camera = new camera_implementation::Camera();
	//camera->Set(playerCenter + CAMERA_OFFSET, playerCenter - glm::vec3(0, -.15, 0), glm::vec3(0, 1, 0));
	//camera->Set(glm::vec3(- 17, 4, 4), glm::vec3(-21, 1, 5), glm::vec3(0, 1, 0));
	camera->Set(glm::vec3(0, 8, 3.5f), glm::vec3(0, 3, 0), glm::vec3(0, 1, 0));

	playerPosition = glm::vec3(camera->GetTargetPosition().x, playerCenter.y, camera->GetTargetPosition().z);

	fov = RADIANS(60);
	width = 0;

	projectionMatrix = glm::perspective(fov, window->props.aspectRatio, 0.01f, 200.0f);

	CreateObjects();

	obstaclePosIdx1 = obstaclePath2.size() - 1 - START_POS_1;
	obstaclePosIdx2 = obstaclePath2.size() - 1 - START_POS_2;
	obstaclePosIdx3 = obstaclePath2.size() - 1 - START_POS_3;
}

void CarRace::CreateVertexPaths(glm::vec3 color)
{
	std::vector<VertexFormat> backboneVertices =
	{
		// dots and labels
		VertexFormat(glm::vec3(-27.36958, 0, 5.38402)),                          // A
		VertexFormat(glm::vec3(-27.23142, 0, 6.97283)),                          // B
		VertexFormat(glm::vec3(-27.093264972894236, 0, 8.768878760601947)),      // C
		VertexFormat(glm::vec3(-26.886028471140012, 0, 10.634007276389962)),     // D
		VertexFormat(glm::vec3(-26.540634301549638, 0, 12.499135792177979)),     // E
		VertexFormat(glm::vec3(-26.126161298041204, 0, 13.897164754800947)),     // F
		//VertexFormat(glm::vec3(-25.459605483161646, 0, 15.059535244014931)),     // G
		VertexFormat(glm::vec3(-24.743033704564983, 0, 15.855726109122333)),     // H
		VertexFormat(glm::vec3(-24.02646192596832, 0, 16.333440628186775)),      // I
		VertexFormat(glm::vec3(-23.071032887839433, 0, 16.691726517485108)),     // J
		VertexFormat(glm::vec3(-22.07579430645518, 0, 16.850964690506586)),      // K
		VertexFormat(glm::vec3(-21.080555725070923, 0, 16.890774233761956)),     // L
		VertexFormat(glm::vec3(-19.84645988415445, 0, 16.612107430974365)),      // N
		VertexFormat(glm::vec3(-19.328935821834637, 0, 16.214011998420666)),     // O
		VertexFormat(glm::vec3(-19.090078562302413, 0, 15.656678392845484)),     // P
		VertexFormat(glm::vec3(-18.891030846025565, 0, 14.94010661424882)),      // Q
		VertexFormat(glm::vec3(-18.851221302770192, 0, 14.064296662630678)),     // R
		VertexFormat(glm::vec3(-18.930840389280934, 0, 13.228296254267905)),     // S
		VertexFormat(glm::vec3(-19.050269019047043, 0, 12.471914932415872)),     // T
		VertexFormat(glm::vec3(-19.408554908345376, 0, 11.83496224032995)),      // U
		VertexFormat(glm::vec3(-19.84645988415445, 0, 11.198009548244027)),      // V
		VertexFormat(glm::vec3(-20.24455531670815, 0, 10.640675942668846)),      // W
		VertexFormat(glm::vec3(-20.443603032985003, 0, 9.924104164072183)),      // Z
		VertexFormat(glm::vec3(-20.443603032985003, 0, 9.247341928730892)),      // A1
		VertexFormat(glm::vec3(-19.76684079764371, 0, 8.80943695292182)),        // B1
		VertexFormat(glm::vec3(-19.010459475791674, 0, 8.65019877990034)),       // C1
		//VertexFormat(glm::vec3((-18.17125, 0, 8.79462))),					     // D1
		VertexFormat(glm::vec3(-17.378268202321497, 0, 9.287151471986261)),      // E1
		//VertexFormat(glm::vec3(-16.86074414000168, 0, 10.362009139881255)),      // F1
		//VertexFormat(glm::vec3(-16.64296823513535, 0, 11.23296296106766)),       // G1
		VertexFormat(glm::vec3(-16.415843420214486, 0, 11.91433740583025)),      // H1
		VertexFormat(glm::vec3(-16.390607329667723, 0, 12.570475760046076)),     // I1
		//VertexFormat(glm::vec3(-16.3401351485742, 0, 13.277086295355428)),       // J1
		VertexFormat(glm::vec3(-16.36537123912096, 0, 14.463182551053269)),      // K1
		VertexFormat(glm::vec3(-15.784941156545422, 0, 15.144556995815858)),     // L1
		VertexFormat(glm::vec3(-15.154038892876356, 0, 15.497862263470534)),     // M1
		VertexFormat(glm::vec3(-14.573608810300817, 0, 15.548334444564059)),     // N1
		VertexFormat(glm::vec3(-14.043650908818801, 0, 15.573570535110822)),     // O1
		VertexFormat(glm::vec3(-13.412748645149739, 0, 15.548334444564059)),     // P1
		VertexFormat(glm::vec3(-12.958499015308012, 0, 15.472626172923771)),     // Q1
		VertexFormat(glm::vec3(-12.579957657106572, 0, 15.295973539096433)),     // R1
		VertexFormat(glm::vec3(-12.201416298905134, 0, 15.018376543082045)),     // S1
		VertexFormat(glm::vec3(-11.747166669063407, 0, 14.589363003787081)),     // T1
		VertexFormat(glm::vec3(-11.39386140140873, 0, 14.08464119285183)),       // U1
		VertexFormat(glm::vec3(-11.141500495941104, 0, 13.655627653556866)),     // V1
		VertexFormat(glm::vec3(-10.91437568102024, 0, 13.049961480434565)),      // W1
		VertexFormat(glm::vec3(-10.762959137739665, 0, 12.31811485457845)),      // Z1
		VertexFormat(glm::vec3(-10.788195228286428, 0, 11.661976500362623)),     // A2
		VertexFormat(glm::vec3(-10.939611771567003, 0, 11.106782508333847)),     // B2
		VertexFormat(glm::vec3(-11.141500495941104, 0, 10.45064415411802)),      // C2
		VertexFormat(glm::vec3(-11.318153129768442, 0, 9.819741890448956)),      // D2
		VertexFormat(glm::vec3(-11.747166669063407, 0, 9.16360353623313)),       // E2
		VertexFormat(glm::vec3(-12.201416298905134, 0, 8.633645634751117)),      // F2
		VertexFormat(glm::vec3(-12.680902019293624, 0, 8.229868186002916)),      // G2
		VertexFormat(glm::vec3(-13.337040373509451, 0, 7.725146375067664)),      // H2
		VertexFormat(glm::vec3(-13.967942637178517, 0, 7.346605016866226)),      // I2
		VertexFormat(glm::vec3(-14.422192267020243, 0, 6.816647115384212)),      // J2
		VertexFormat(glm::vec3(-14.725025353581394, 0, 6.21098094226191)),       // K2
		VertexFormat(glm::vec3(-14.87644189686197, 0, 5.630550859686371)),       // L2
		VertexFormat(glm::vec3(-14.87644189686197, 0, 4.974412505470545)),       // M2
		VertexFormat(glm::vec3(-14.674553172487869, 0, 4.469690694535293)),      // N2
		VertexFormat(glm::vec3(-14, 0, 4)),                                      // O2
		VertexFormat(glm::vec3(-13.463220826243264, 0, 3.813552340319467)),      // P2
		VertexFormat(glm::vec3(-12.781846381480674, 0, 3.6116636159453663)),     // Q2
		VertexFormat(glm::vec3(-12.150944117811608, 0, 3.510719253758316)),      // R2
		VertexFormat(glm::vec3(-11.469569673049017, 0, 3.4602470726647914)),     // S2
		VertexFormat(glm::vec3(-10.737723047192903, 0, 3.485483163211554)),      // T2
		VertexFormat(glm::vec3(-10.106820783523837, 0, 3.636899706492129)),      // U2
		VertexFormat(glm::vec3(-9.475918519854773, 0, 3.9649688836000423)),      // V2
		VertexFormat(glm::vec3(-8.794544075092182, 0, 4.368746332348243)),       // W2
		VertexFormat(glm::vec3(-8.113169630329592, 0, 4.999648596017307)),       // Z2
		VertexFormat(glm::vec3(-7.507503457207289, 0, 5.630550859686371)),       // A3
		VertexFormat(glm::vec3(-6.977545555725274, 0, 6.412869666636011)),       // B3
		VertexFormat(glm::vec3(-6.674712469164123, 0, 7.220424564132413)),       // C3
		VertexFormat(glm::vec3(-6.498059835336785, 0, 7.977507280535289)),       // D3
		VertexFormat(glm::vec3(-6.371879382602971, 0, 8.835534359125218)),       // E3
		VertexFormat(glm::vec3(-6.321407201509446, 0, 9.542144894434568)),       // F3
		VertexFormat(glm::vec3(-6.296171110962684, 0, 10.34969979193097)),       // G3
		VertexFormat(glm::vec3(-6.270935020415921, 0, 11.03107423669356)),       // H3
		VertexFormat(glm::vec3(-6.296171110962684, 0, 11.586268228722336)),      // I3
		VertexFormat(glm::vec3(-6.296171110962684, 0, 12.2171704923914)),        // J3
		VertexFormat(glm::vec3(-6.2456989298691585, 0, 12.974253208794277)),     // K3
		VertexFormat(glm::vec3(-6.094282386588583, 0, 13.706099834650392)),      // L3
		VertexFormat(glm::vec3(-5.917629752761245, 0, 14.589363003787081)),      // M3
		VertexFormat(glm::vec3(-5.715741028387144, 0, 15.447390082377009)),      // N3
		VertexFormat(glm::vec3(-5.412907941825993, 0, 16.35588934206046)),       // O3
		VertexFormat(glm::vec3(-4.882950040343978, 0, 17.11297205846334)),       // P3
		VertexFormat(glm::vec3(-4.2772838672216755, 0, 17.693402141038877)),     // Q3
		VertexFormat(glm::vec3(-3.520201150818797, 0, 18.071943499240316)),      // R3
		VertexFormat(glm::vec3(-2.7631184344159188, 0, 18.273832223614416)),     // S3
		VertexFormat(glm::vec3(-2.1574522612936162, 0, 18.32430440470794)),      // T3
		VertexFormat(glm::vec3(-1.5517860881713137, 0, 18.32430440470794)),      // U3
		VertexFormat(glm::vec3(-0.9461199150490113, 0, 18.32430440470794)),      // V3
		VertexFormat(glm::vec3(-0.44139810411375907, 0, 18.19812395197413)),     // W3
		VertexFormat(glm::vec3(0, 0, 18)),                                       // Z3
		VertexFormat(glm::vec3(0.3156846122891191, 0, 17.592457778851827)),      // A4
		VertexFormat(glm::vec3(0.5680455177567452, 0, 17.1382081490101)),        // B4
		VertexFormat(glm::vec3(0.8204064232243713, 0, 16.683958519168375)),      // C4
		VertexFormat(glm::vec3(0.9213507854114217, 0, 16.204472798779886)),      // D4
		VertexFormat(glm::vec3(0.8961146948646591, 0, 15.699750987844633)),      // E4
		VertexFormat(glm::vec3(0.8456425137711339, 0, 15.094084814722333)),      // F4
		VertexFormat(glm::vec3(0.8456425137711339, 0, 14.513654732146794)),      // G4
		VertexFormat(glm::vec3(0.769934242130846, 0, 14.008932921211542)),       // H4
		//VertexFormat(glm::vec3(0.5680455177567452, 0, 13.504211110276291)),      // I4
		//VertexFormat(glm::vec3(0.3409207028358817, 0, 13.150905842621615)),      // J4
		//VertexFormat(glm::vec3(0.18950415955530608, 0, 12.671420122233126)),     // K4
		VertexFormat(glm::vec3(0, 0, 12)),                                       // L4
		VertexFormat(glm::vec3(-0.0880928364590826, 0, 11.460087775988523)),     // M4
		VertexFormat(glm::vec3(-0.18581, 0, 10.96135)),							 // N4
		VertexFormat(glm::vec3(0, 0, 10.34969979193097)),                        // O4
		VertexFormat(glm::vec3(0.2904485217423565, 0, 9.945922343182769)),       // P4
		VertexFormat(glm::vec3(0.7951703326776086, 0, 9.76926970935543)),        // Q4
		VertexFormat(glm::vec3(1.350364324706386, 0, 9.794505799902193)),        // R4
		VertexFormat(glm::vec3(2, 0, 10)),                                       // S4
		VertexFormat(glm::vec3(2.4859883993107035, 0, 10.703005059585646)),      // T4
		VertexFormat(glm::vec3(2.94023802915243, 0, 11.510559957082048)),        // U4
		VertexFormat(glm::vec3(3.3440154779006317, 0, 12.292878764031688)),      // V4
		VertexFormat(glm::vec3(3.6468485644617834, 0, 13.150905842621615)),      // W4
		VertexFormat(glm::vec3(4, 0, 14)),                                       // Z4
		VertexFormat(glm::vec3(4.302986918677611, 0, 14.740779547067657)),       // A5
		VertexFormat(glm::vec3(4.479639552504949, 0, 15.497862263470534)),       // B5
		VertexFormat(glm::vec3(4.8581809107063885, 0, 16.280181070420173)),      // C5
		VertexFormat(glm::vec3(5.287194450001353, 0, 17.012027696276288)),       // D5
		VertexFormat(glm::vec3(5.817152351483367, 0, 17.693402141038877)),       // E5
		VertexFormat(glm::vec3(6.599471158433008, 0, 17.92052695595974)),        // F5
		VertexFormat(glm::vec3(7.174510940032555, 0, 17.99314381647879)),        // G5
		VertexFormat(glm::vec3(8, 0, 18)),                                       // H5
		VertexFormat(glm::vec3(8.585173705709238, 0, 18.043524629538673)),       // I5
		VertexFormat(glm::vec3(8.98822021018829, 0, 17.892382190359026)),        // J5
		VertexFormat(glm::vec3(9.391266714667342, 0, 17.66566853158956)),        // K5
		VertexFormat(glm::vec3(9.743932406086513, 0, 17.36338365323027)),        // L5
		VertexFormat(glm::vec3(10.071407690975743, 0, 17.0107179618111)),        // M5
		VertexFormat(glm::vec3(10.348502162805092, 0, 16.607671457332046)),      // N5
		VertexFormat(glm::vec3(10.499644601984738, 0, 16.154244139793114)),      // O5
		VertexFormat(glm::vec3(10.449263788924856, 0, 15.675626415724238)),      // P5
		VertexFormat(glm::vec3(10.424073382394914, 0, 15.146627878595481)),      // Q5
		VertexFormat(glm::vec3(10.348502162805092, 0, 14.642819747996667)),      // R5
		VertexFormat(glm::vec3(10, 0, 14)),                                      // S5
		//VertexFormat(glm::vec3(9.743932406086513, 0, 13.584822673739154)),       // T5
		//VertexFormat(glm::vec3(9.441647527727225, 0, 13.206966575790041)),       // U5
		//VertexFormat(glm::vec3(9.114172242837995, 0, 12.803920071310989)),       // V5
		//VertexFormat(glm::vec3(8.736316144888882, 0, 12.451254379891818)),       // W5
		//VertexFormat(glm::vec3(8, 0, 12)),                                       // Z5
		//VertexFormat(glm::vec3(7.577557444511607, 0, 11.594780557873833)),       // A6
		//VertexFormat(glm::vec3(7.199701346562494, 0, 11.317686086044484)),       // B6
		//VertexFormat(glm::vec3(6.821845248613383, 0, 10.91463958156543)),        // C6
		//VertexFormat(glm::vec3(6.318037118014567, 0, 10.561973890146259)),       // D6
		//VertexFormat(glm::vec3(5.62336, 0, 10.03566)),                           // M
		//VertexFormat(glm::vec3(5.02332, 0, 9.47486)),                            // E6
		//VertexFormat(glm::vec3(4.58149559340669, 0, 8.996219378219669)),         // F6
		//VertexFormat(glm::vec3(3.9923993475271136, 0, 8.480760163075038)),       // G6
		//VertexFormat(glm::vec3(3.5137586477499574, 0, 8.075756494032829)),       // H6
		//VertexFormat(glm::vec3(2.94562, 0, 7.45139)),                            // I6
		//VertexFormat(glm::vec3(2.463904918933628, 0, 6.758222504125202)),        // N6
		//VertexFormat(glm::vec3(2, 0, 6)),                                        // O6
		//VertexFormat(glm::vec3(1.7837639426252272, 0, 5.448321364568281)),       // P6
		//VertexFormat(glm::vec3(1.481479064265938, 0, 4.969703640499406)),        // Q6
		VertexFormat(glm::vec3(1.3807174381461749, 0, 4.44070510337065)),        // R6
		VertexFormat(glm::vec3(1.3051462185563525, 0, 3.886516159711953)),       // S6
		VertexFormat(glm::vec3(1.3051462185563525, 0, 3.3323272160532555)),      // T6
		VertexFormat(glm::vec3(1.4059078446761155, 0, 2.82851908545444)),        // U6
		VertexFormat(glm::vec3(1.6326215034455827, 0, 2.2995205483256838)),      // V6
		VertexFormat(glm::vec3(2, 0, 2)),                                        // W6
		VertexFormat(glm::vec3(2.4387145124036875, 0, 1.669760385077164)),       // Z6
		VertexFormat(glm::vec3(3.0180938625923255, 0, 1.3170946936579933)),      // A7
		VertexFormat(glm::vec3(3.6478540258408447, 0, 1.0903810348885261)),      // B7
		VertexFormat(glm::vec3(4.252423782559424, 0, 0.9140481891789407)),       // C7
		VertexFormat(glm::vec3(4.856993539278002, 0, 0.8636673761190592)),       // D7
		VertexFormat(glm::vec3(5.461563295996581, 0, 0.8132865630591776)),       // E7
		VertexFormat(glm::vec3(6.015752239655278, 0, 0.8132865630591776)),       // F7
		VertexFormat(glm::vec3(6.670702809433738, 0, 0.8132865630591776)),       // G7
		VertexFormat(glm::vec3(7.350843785742139, 0, 0.7880961565292368)),       // H7
		VertexFormat(glm::vec3(8.081365575110421, 0, 0.8132865630591776)),       // I7
		VertexFormat(glm::vec3(8.761506551418822, 0, 0.9140481891789407)),       // J7
		VertexFormat(glm::vec3(9.492028340787106, 0, 0.9392385957088815)),       // K7
		VertexFormat(glm::vec3(10.29812134974521, 0, 1.0148098152987037)),       // L7
		VertexFormat(glm::vec3(11.079023952173374, 0, 1.1407618479484076)),      // M7
		VertexFormat(glm::vec3(11.834736148071599, 0, 1.3170946936579933)),      // N7
		VertexFormat(glm::vec3(12.51487712438, 0, 1.694950791607105)),           // O7
		VertexFormat(glm::vec3(13.245398913748282, 0, 2.022426076496335)),       // P7
		VertexFormat(glm::vec3(14.076682329236329, 0, 2.475853394035269)),       // Q7
		VertexFormat(glm::vec3(14.580490459835143, 0, 3.15599437034367)),        // R7
		VertexFormat(glm::vec3(15.059108183904018, 0, 3.861325753182012)),       // S7
		VertexFormat(glm::vec3(15.487345094913012, 0, 4.541466729490413)),       // T7
		VertexFormat(glm::vec3(15.840010786332183, 0, 5.2971789253886366)),      // U7
		VertexFormat(glm::vec3(16.343337684434154, 0, 6.251566414462545)),       // V7
		VertexFormat(glm::vec3(16.678051460502097, 0, 7.3561218754867514)),      // W7
		VertexFormat(glm::vec3(16.912351103749653, 0, 8.427205958904164)),       // Z7
		VertexFormat(glm::vec3(17.11317936939042, 0, 9.431347287107988)),        // A8
		VertexFormat(glm::vec3(17.28053625742439, 0, 10.5024313705254)),         // B8
		VertexFormat(glm::vec3(17.28053625742439, 0, 11.606986831549607)),       // C8
		VertexFormat(glm::vec3(17.314007635031185, 0, 12.61112815975343)),       // D8
		VertexFormat(glm::vec3(17.04623661417683, 0, 14.485525305733903)),       // F8
		VertexFormat(glm::vec3(17.146650746997214, 0, 15.288838368296963)),      // G8
		VertexFormat(glm::vec3(17.58177865588554, 0, 16.527279339748347)),       // H8
		VertexFormat(glm::vec3(18.08384931998745, 0, 17.431006535131786)),       // I8
		VertexFormat(glm::vec3(18.686334116909745, 0, 18.10043408726767)),       // J8
		VertexFormat(glm::vec3(19.255347536225244, 0, 18.5020906185492)),        // K8
		VertexFormat(glm::vec3(19.891303710754332, 0, 18.803333017010345)),      // L8
		VertexFormat(glm::vec3(20.6611453957106, 0, 19.071104037864696)),        // M8
		VertexFormat(glm::vec3(21.59834396870084, 0, 19.204989548291874)),       // N8
		VertexFormat(glm::vec3(22.468599786477487, 0, 19.33887505871905)),       // O8
		VertexFormat(glm::vec3(23.171498716220164, 0, 19.305403681112256)),      // P8
		VertexFormat(glm::vec3(23.94134040117643, 0, 19.138046793078285)),       // Q8
		VertexFormat(glm::vec3(24.610767953312312, 0, 18.93721852743752)),       // R8
		VertexFormat(glm::vec3(25.280195505448194, 0, 18.60250475136958)),       // S8
		VertexFormat(glm::vec3(26, 0, 18)),                                      // T8
		VertexFormat(glm::vec3(26.485165099292786, 0, 17.531420667952165)),      // U8
		VertexFormat(glm::vec3(26.78640749775393, 0, 16.92893587102987)),        // V8
		VertexFormat(glm::vec3(27.121121273821874, 0, 16.1925655636804)),        // W8
		VertexFormat(glm::vec3(27.288478161855846, 0, 15.489666633937723)),      // Z8
		VertexFormat(glm::vec3(27.42236367228302, 0, 14.753296326588252)),       // A9
		VertexFormat(glm::vec3(27.455835049889814, 0, 13.983454641631988)),      // B9
		VertexFormat(glm::vec3(27.455835049889814, 0, 13.146670201462134)),      // C9
		VertexFormat(glm::vec3(27.388892294676225, 0, 12.376828516505869)),      // D9
		VertexFormat(glm::vec3(27.221535406642257, 0, 11.6404582091564)),        // E9
		VertexFormat(glm::vec3(26.987235763394697, 0, 10.870616524200134)),      // F9
		VertexFormat(glm::vec3(26.78640749775393, 0, 10.301603104884633)),       // G9
		VertexFormat(glm::vec3(26.55210785450637, 0, 9.598704175141958)),        // H9
		VertexFormat(glm::vec3(26.183922700831637, 0, 8.89580524539928)),        // I9
		VertexFormat(glm::vec3(25.8157375471569, 0, 8.293320448476985)),         // J9
		VertexFormat(glm::vec3(25.380609638268577, 0, 7.824721161981867)),       // K9
		VertexFormat(glm::vec3(24.811596218953078, 0, 7.289179120273162)),       // L9
		VertexFormat(glm::vec3(24.342996932457957, 0, 6.753637078564456)),       // M9
		VertexFormat(glm::vec3(23.807454890749252, 0, 6.251566414462544)),       // N9
		VertexFormat(glm::vec3(23.506212492288107, 0, 5.81643850557422)),        // O9
		VertexFormat(glm::vec3(23.238441471433752, 0, 5.247425086258719)),       // P9
		VertexFormat(glm::vec3(23.07108458339978, 0, 4.5779975341228365)),       // Q9
		VertexFormat(glm::vec3(23.07108458339978, 0, 3.9420413595937482)),       // R9
		VertexFormat(glm::vec3(23.573155247501692, 0, 3.406499317885042)),       // S9
		VertexFormat(glm::vec3(24.041754533996812, 0, 2.837485898569542)),       // T9
		VertexFormat(glm::vec3(24.610767953312312, 0, 2.368886612074424)),       // U9
		VertexFormat(glm::vec3(25.07936723980743, 0, 1.9002873255793062)),       // V9
		VertexFormat(glm::vec3(25.514495148695755, 0, 1.3647452838706)),         // W9
		VertexFormat(glm::vec3(26.016565812797666, 0, 0.7957318645550998)),      // Z9
		VertexFormat(glm::vec3(26.485165099292786, 0, 0.19324706763280544)),     // A10
		VertexFormat(glm::vec3(26.719464742540342, 0, -0.4092377292894889)),     // B10
		VertexFormat(glm::vec3(26.92029300818111, 0, -1.1121366590321657)),      // C10
		VertexFormat(glm::vec3(27.188064029035463, 0, -1.9154497215952249)),     // D10
		VertexFormat(glm::vec3(27.35542091706943, 0, -2.8191769169786665)),      // E10
		VertexFormat(glm::vec3(27.321949539462636, 0, -3.8233182451824903)),     // F10
		VertexFormat(glm::vec3(27.15459265142867, 0, -4.526217174925168)),       // G10
		VertexFormat(glm::vec3(26.92029300818111, 0, -5.296058859881432)),       // H10
		VertexFormat(glm::vec3(26.51863647689958, 0, -5.9320150344105205)),      // I10
		VertexFormat(glm::vec3(26.05003719040446, 0, -6.668385341759992)),       // J10
		VertexFormat(glm::vec3(25.380609638268577, 0, -7.30434151628908)),       // K10
		VertexFormat(glm::vec3(24.37646831006475, 0, -7.5721125371434335)),      // L10
		VertexFormat(glm::vec3(23.439269737074518, 0, -7.739469425177404)),      // M10
		VertexFormat(glm::vec3(22.435128408870693, 0, -7.772940802784198)),      // N10
		VertexFormat(glm::vec3(21.397515703060073, 0, -7.806412180390992)),      // O10
		VertexFormat(glm::vec3(20.493788507676634, 0, -7.605583914750228)),      // P10
		VertexFormat(glm::vec3(19.556589934686397, 0, -7.30434151628908)),       // Q10
		VertexFormat(glm::vec3(18.719805494516542, 0, -6.902684985007551)),      // R10
		VertexFormat(glm::vec3(17.8160782991331, 0, -6.601442586546403)),        // S10
		VertexFormat(glm::vec3(16.94582248135645, 0, -6.099371922444491)),       // T10
		VertexFormat(glm::vec3(16.109038041186597, 0, -5.697715391162962)),      // U10
		VertexFormat(glm::vec3(15.17183946819636, 0, -5.4299443703086085)),      // V10
		VertexFormat(glm::vec3(14.335055028026508, 0, -5.19564472706105)),       // W10
		VertexFormat(glm::vec3(13.46479921024986, 0, -5.162173349454256)),       // Z10
		VertexFormat(glm::vec3(12.594543392473211, 0, -5.162173349454256)),      // A11
		VertexFormat(glm::vec3(11.791230329910153, 0, -5.496887125522197)),      // B11
		VertexFormat(glm::vec3(11.088331400167474, 0, -5.898543656803727)),      // C11
		VertexFormat(glm::vec3(10.48584660324518, 0, -6.300200188085256)),       // D11
		VertexFormat(glm::vec3(10.017247316750062, 0, -6.802270852187168)),      // E11
		VertexFormat(glm::vec3(9.582119407861738, 0, -7.2708701386822865)),      // F11
		VertexFormat(glm::vec3(9.146991498973415, 0, -7.839883557997786)),       // G11
		VertexFormat(glm::vec3(8.812277722905474, 0, -8.408896977313287)),       // H11
		VertexFormat(glm::vec3(8.243264303589973, 0, -8.910967641415198)),       // I11
		VertexFormat(glm::vec3(7.774665017094855, 0, -9.546923815944288)),       // J11
		VertexFormat(glm::vec3(7.272594352992942, 0, -10.182879990473376)),      // K11
		VertexFormat(glm::vec3(6.803995066497825, 0, -10.818836165002464)),      // L11
		VertexFormat(glm::vec3(6.301924402395913, 0, -11.421320961924758)),      // M11
		VertexFormat(glm::vec3(5.565554095046441, 0, -11.923391626026671)),      // N11
		VertexFormat(glm::vec3(4.728769654876587, 0, -12.325048157308201)),      // O11
		VertexFormat(glm::vec3(3.925456592313528, 0, -12.726704688589729)),      // P11
		VertexFormat(glm::vec3(2.988258019323292, 0, -13.094889842264465)),      // Q11
		VertexFormat(glm::vec3(1.9506453135126733, 0, -13.228775352691642)),     // R11
		VertexFormat(glm::vec3(1.0803894957360254, 0, -13.161832597478053)),     // S11
		VertexFormat(glm::vec3(0.31054781077976007, 0, -12.96100433183729)),     // T11
		VertexFormat(glm::vec3(-0.49276525178329944, 0, -12.525876422948965)),   // U11
		VertexFormat(glm::vec3(-1.296078314346359, 0, -11.990334381240258)),     // V11
		VertexFormat(glm::vec3(-1.998977244089036, 0, -11.35437820671117)),      // W11
		VertexFormat(glm::vec3(-2.6014620410113305, 0, -10.651479276968493)),    // Z11
		VertexFormat(glm::vec3(-3.0700613275064486, 0, -10.149408612866582)),    // A12
		VertexFormat(glm::vec3(-3.6056033692151552, 0, -9.513452438337493)),     // B12
		VertexFormat(glm::vec3(-4.141145410923861, 0, -8.877496263808405)),      // C12
		VertexFormat(glm::vec3(-4.643216075025774, 0, -8.074183201245345)),      // D12
		VertexFormat(glm::vec3(-5.078343983914097, 0, -7.438227026716257)),      // E12
		VertexFormat(glm::vec3(-5.480000515195627, 0, -6.936156362614344)),      // F12
		VertexFormat(glm::vec3(-5.948599801690744, 0, -6.393920045384281)),      // G12
		VertexFormat(glm::vec3(-6.4272405014679, 0, -6.025734891709545)),        // H12
		//VertexFormat(glm::vec3(-7.089973778082424, 0, -5.841642314872177)),      // I12
		VertexFormat(glm::vec3(-7.679070023962002, 0, -5.915279345607125)),      // J12
		VertexFormat(glm::vec3(-8.19452923910663, 0, -6.320283014649334)),       // K12
		VertexFormat(glm::vec3(-8.746806969618735, 0, -6.68846816832407)),       // L12
		VertexFormat(glm::vec3(-9.33590321549831, 0, -7.167108868101225)),       // M12
		//VertexFormat(glm::vec3(-9.888180946010415, 0, -7.535294021775961)),      // N12
		//VertexFormat(glm::vec3(-10.36682164578757, 0, -7.903479175450697)),      // O12
		//VertexFormat(glm::vec3(-10.919099376299675, 0, -8.345301359860379)),     // P12
		//VertexFormat(glm::vec3(-11.360921560709357, 0, -8.823942059637536)),     // Q12
		//VertexFormat(glm::vec3(-11.839562260486513, 0, -9.413038305517112)),     // R12
		//VertexFormat(glm::vec3(-12.20608, 0, -9.87497)),                         // S12
		VertexFormat(glm::vec3(-12.649569598570933, 0, -10.554412281908792)),    // T12
		VertexFormat(glm::vec3(-13.275484359817982, 0, -11.03305298168595)),     // U12
		VertexFormat(glm::vec3(-13.827762090330086, 0, -11.548512196830579)),    // V12
		VertexFormat(glm::vec3(-14.343221305474716, 0, -11.990334381240261)),    // W12
		VertexFormat(glm::vec3(-14.89549903598682, 0, -12.542612111752366)),     // Z12
		//VertexFormat(glm::vec3(-15.631869343336291, 0, -12.837160234692153)),    // A13
		//VertexFormat(glm::vec3((-16.0502, 0, -12.44442))),
		//VertexFormat(glm::vec3(-16.589150742890602, 0, -12.837160234692153)),    // B13
		VertexFormat(glm::vec3(-17.251884019505127, 0, -12.248063988812577)),    // C13
		VertexFormat(glm::vec3(-17.767343234649758, 0, -11.511693681463106)),    // D13
		VertexFormat(glm::vec3(-18.172346903691967, 0, -10.664867828011213)),    // E13
		VertexFormat(glm::vec3(-18.28280244979439, 0, -9.781223459191848)),      // F13
		VertexFormat(glm::vec3(-18.50371354199923, 0, -8.639849482800168)),      // G13
		VertexFormat(glm::vec3(-18.466895026631754, 0, -7.535294021775962)),     // H13
		VertexFormat(glm::vec3(-18.20916541905944, 0, -6.320283014649334)),      // I13
		VertexFormat(glm::vec3(-17.767343234649758, 0, -5.252546068992601)),     // J13
		VertexFormat(glm::vec3(-17.472795111709967, 0, -4.147990607968394)),     // K13
		VertexFormat(glm::vec3(-17.472795111709967, 0, -3.227527723781555)),     // L13
		VertexFormat(glm::vec3(-17.730524719282283, 0, -2.527975931799557)),     // M13
		VertexFormat(glm::vec3(-18, 0, -2)),                                     // N13
		VertexFormat(glm::vec3(-18.5405320573667, 0, -1.4234204707753506)),      // O13
		VertexFormat(glm::vec3(-19.313720880083647, 0, -0.9447797709981942)),    // P13
		VertexFormat(glm::vec3(-20.123728218168065, 0, -0.539776101955985)),     // Q13
		VertexFormat(glm::vec3(-20.860098525517536, 0, -0.28204649438367013)),   // R13
		VertexFormat(glm::vec3(-21.670105863601954, 0, 0)),                      // S13
		VertexFormat(glm::vec3(-22.66420577852374, 0, 0.30704975149590685)),     // T13
		VertexFormat(glm::vec3(-23.58467, 0, 0.63842)),                          // U13
		VertexFormat(glm::vec3(-24.468313031529945, 0, 0.9697830281104309)),     // V13
		VertexFormat(glm::vec3(-25.35195740034931, 0, 1.5220607586225343)),      // W13
		VertexFormat(glm::vec3(-26, 0, 2)),                                      // Z13
		VertexFormat(glm::vec3(-26.456512861373522, 0, 2.7738902811166364)),     // A14
		VertexFormat(glm::vec3(-26.86151653041573, 0, 3.5838976192010548)),      // B14
		VertexFormat(glm::vec3(-27.37697574556036, 0, 4.393904957285473))        // C14
		//VertexFormat(glm::vec3((-27.37195, 0, 5.2759)))						 // J6
	};

	std::vector<VertexFormat> backboneVertices_MediumStep, backboneVertices_SmallStep;
	glm::vec3 d, p, p1, p2, newPosition;
	GLuint currIndice = 0;


	// create complex backboneVertices vectors
	for (int i = 0; i < backboneVertices.size() - 1; i++) {
		p1 = backboneVertices[i].position;
		p2 = backboneVertices[i + 1].position;

		backboneVertices_MediumStep.push_back(backboneVertices[i]);
		backboneVertices_SmallStep.push_back(backboneVertices[i]);

		for (float j = STEP_MEDIUM; j <= MAX_STEP_MEDIUM; j += STEP_MEDIUM) {
			newPosition = glm::mix(p1, p2, j);
			backboneVertices_MediumStep.push_back(VertexFormat(newPosition));
		}

		for (float j = STEP_SMALL; j <= MAX_STEP_SMALL; j += STEP_SMALL) {
			newPosition = glm::mix(p1, p2, j);
			backboneVertices_SmallStep.push_back(VertexFormat(newPosition));
		}
	}

	p1 = backboneVertices[backboneVertices.size() - 1].position;
	p2 = backboneVertices[0].position;

	backboneVertices_MediumStep.push_back(backboneVertices[backboneVertices.size() - 1]);
	backboneVertices_SmallStep.push_back(backboneVertices[backboneVertices.size() - 1]);

	for (float j = STEP_MEDIUM; j <= MAX_STEP_MEDIUM; j += STEP_MEDIUM) {
		newPosition = glm::mix(p1, p2, j);
		backboneVertices_MediumStep.push_back(VertexFormat(newPosition));
	}

	for (float j = STEP_SMALL; j <= MAX_STEP_SMALL; j += STEP_SMALL) {
		newPosition = glm::mix(p1, p2, j);
		backboneVertices_SmallStep.push_back(VertexFormat(newPosition));
	}


	// create paths for obstacles
	for (int i = 0; i < backboneVertices_SmallStep.size() - 1; i++) {
		p1 = backboneVertices_SmallStep[i].position;
		p2 = backboneVertices_SmallStep[i + 1].position;
		d = p2 - p1;
		p = glm::normalize(glm::cross(d, glm::vec3(0, 1, 0)));

		// obstacle1 path
		obstaclePath1.emplace_back(p1 + p * DIST_PATH_1 + glm::vec3(0, OBSTACLE_COORD_Y, 0));

		// obstacle2 path
		obstaclePath2.emplace_back(p1 + p * DIST_PATH_2 + glm::vec3(0, OBSTACLE_COORD_Y, 0));

		// obstacle3 path
		obstaclePath3.emplace_back(p1 + p * DIST_PATH_3 + glm::vec3(0, OBSTACLE_COORD_Y, 0));
	}

	p1 = backboneVertices_SmallStep[backboneVertices_SmallStep.size() - 1].position;
	p2 = backboneVertices_SmallStep[0].position;
	d = p2 - p1;
	p = glm::cross(d, glm::vec3(0, 1, 0));

	// obstacle1 path
	obstaclePath1.emplace_back(p1 + p * DIST_PATH_1 + glm::vec3(0, OBSTACLE_COORD_Y, 0));

	// obstacle2 path
	obstaclePath2.emplace_back(p1 + p * DIST_PATH_2 + glm::vec3(0, OBSTACLE_COORD_Y, 0));

	// obstacle3 path
	obstaclePath3.emplace_back(p1 + p * DIST_PATH_3 + glm::vec3(0, OBSTACLE_COORD_Y, 0));


	// create inner/outer track vertices and main track vertices and indices vectors
	for (int i = 0; i < backboneVertices_MediumStep.size() - 1; i++) {
		p1 = backboneVertices_MediumStep[i].position;
		p2 = backboneVertices_MediumStep[i + 1].position;
		d = p2 - p1;
		p = glm::normalize(glm::cross(d, glm::vec3(0, 1, 0)));

		// interior vertex
		trackVertices.emplace_back(glm::vec3(p1 + p * DIST_TO_BACKBONE), color);
		trackInnerVertices.emplace_back(glm::vec3(p1 + p * DIST_TO_BACKBONE), color);

		// exterior vertex
		trackVertices.emplace_back(glm::vec3(p1 - p * DIST_TO_BACKBONE), color);
		trackOuterVertices.emplace_back(glm::vec3(p1 - p * DIST_TO_BACKBONE), color);

		trackIndices.emplace_back(currIndice++);
		trackIndices.emplace_back(currIndice++);
	}

	p1 = backboneVertices_MediumStep[backboneVertices_MediumStep.size() - 1].position;
	p2 = backboneVertices_MediumStep[0].position;
	d = p2 - p1;
	p = glm::cross(d, glm::vec3(0, 1, 0));

	// interior vertex
	trackVertices.emplace_back(glm::vec3(p1 + p * DIST_TO_BACKBONE), color);
	trackInnerVertices.emplace_back(glm::vec3(p1 + p * DIST_TO_BACKBONE), color);

	// exterior vertex
	trackVertices.emplace_back(glm::vec3(p1 - p * DIST_TO_BACKBONE), color);
	trackOuterVertices.emplace_back(glm::vec3(p1 - p * DIST_TO_BACKBONE), color);

	trackIndices.emplace_back(currIndice++);
	trackIndices.emplace_back(currIndice);

	trackIndices.emplace_back(0);
	trackIndices.emplace_back(1);

	/*CreateMesh(name, trackVertices, trackIndices);
	meshes[name]->SetDrawMode(GL_TRIANGLE_STRIP);*/
}

Mesh* CarRace::CreateSky(
	const std::string& name,
	glm::vec3 leftBottomCorner,
	float length,
	float height,
	glm::vec3 colorBottom,
	glm::vec3 colorTop)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, colorBottom),
		VertexFormat(corner + glm::vec3(length, 0, 0), colorBottom),
		VertexFormat(corner + glm::vec3(length, height, 0), colorTop),
		VertexFormat(corner + glm::vec3(0, height, 0), colorTop)
	};

	Mesh* sky = new Mesh(name);
	std::vector<unsigned int> indices = { 0, 1, 2, 3 };

	indices.push_back(0);
	indices.push_back(2);

	sky->InitFromData(vertices, indices);
	return sky;
}


void CarRace::CreateObjects()
{
	CreateVertexPaths(RACE_TRACK_COLOR);
	Mesh* raceTrack = new Mesh("raceTrack");
	raceTrack->InitFromData(trackVertices, trackIndices);
	raceTrack->SetDrawMode(GL_TRIANGLE_STRIP);
	AddMeshToList(raceTrack);

	Mesh* skySide = CreateSky("sky_side", glm::vec3(0, 0, 0), SKY_LENGTH, SKY_HEIGHT, SKY_LIGHT_BLUE, SKY_DARK_BLUE);
	AddMeshToList(skySide);

	Mesh* skyTop = CreateSky("sky_top", glm::vec3(0, 0, 0), SKY_LENGTH, SKY_LENGTH, SKY_DARK_BLUE, SKY_DARK_BLUE);
	AddMeshToList(skyTop);

	Mesh* lightTree = new Mesh("light_tree");
	lightTree->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "vegetation/trees/light_tree"), "light_tree.fbx");
	AddMeshToList(lightTree);

	Mesh* darkTree = new Mesh("dark_tree");
	darkTree->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "vegetation/trees/dark_tree"), "dark_tree.fbx");
	AddMeshToList(darkTree);

	Mesh* orangeTree = new Mesh("orange_tree");
	orangeTree->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "vegetation/trees/orange_tree"), "orange_tree.fbx");
	AddMeshToList(orangeTree);

	Mesh* yellowTree = new Mesh("yellow_tree");
	yellowTree->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "vegetation/trees/yellow_tree"), "yellow_tree.fbx");
	AddMeshToList(yellowTree);

	Mesh* greenForest = new Mesh("green_forest");
	greenForest->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "vegetation/trees/green_forest"), "green_forest.fbx");
	AddMeshToList(greenForest);

	Mesh* autumnForest = new Mesh("autumn_forest");
	autumnForest->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "vegetation/trees/autumn_forest"), "autumn_forest.fbx");
	AddMeshToList(autumnForest);

	Mesh* grass2 = new Mesh("grass2");
	grass2->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "vegetation/grass/grass2"), "grass2.fbx");
	AddMeshToList(grass2);

	Mesh* player = new Mesh("player");
	player->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "characters/race_cars/player"), "player.fbx");
	AddMeshToList(player);

	Mesh* obstacle1 = new Mesh("obstacle1");
	obstacle1->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "characters/race_cars/obstacle1"), "obstacle1.fbx");
	AddMeshToList(obstacle1);

	Mesh* obstacle2 = new Mesh("obstacle2");
	obstacle2->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "characters/race_cars/obstacle2"), "obstacle2.fbx");
	AddMeshToList(obstacle2);

	Mesh* obstacle3 = new Mesh("obstacle3");
	obstacle3->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "characters/race_cars/obstacle3"), "obstacle3.fbx");
	AddMeshToList(obstacle3);

	// DEBUG
	Mesh* mesh = new Mesh("sphere");
	mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
	meshes[mesh->GetMeshID()] = mesh;

	Mesh* mesh_box = new Mesh("box");
	mesh_box->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
	meshes[mesh_box->GetMeshID()] = mesh_box;
}

void CarRace::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// Sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void CarRace::RenderGrass() {
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0));
	RenderMesh(meshes["grass2"], shaders["Simple"], modelMatrix);
}

void CarRace::RenderRaceTrack()
{
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, .01, 0));
	RenderMesh(meshes["raceTrack"], shaders["VertexColor"], modelMatrix);
}

void CarRace::RenderSky()
{
	{
		modelMatrix = Translate(-SKY_LENGTH / 2, 0, -SKY_LENGTH / 2);
		RenderMesh(meshes["sky_side"], shaders["VertexColor"], modelMatrix);

		modelMatrix = Translate(-SKY_LENGTH / 2, SKY_HEIGHT, -SKY_LENGTH / 2);
		RenderMesh(meshes["sky_top"], shaders["VertexColor"], modelMatrix);
	}

	{
		modelMatrix = Translate(SKY_LENGTH / 2, 0, -SKY_LENGTH / 2);
		modelMatrix *= RotateOY(-M_PI_2);
		RenderMesh(meshes["sky_side"], shaders["VertexColor"], modelMatrix);

		modelMatrix = Translate(SKY_LENGTH / 2, SKY_HEIGHT, -SKY_LENGTH / 2);
		modelMatrix *= RotateOY(-M_PI_2);
		RenderMesh(meshes["sky_top"], shaders["VertexColor"], modelMatrix);
	}

	{
		modelMatrix = Translate(-SKY_LENGTH / 2, 0, SKY_LENGTH / 2);
		RenderMesh(meshes["sky_side"], shaders["VertexColor"], modelMatrix);

		modelMatrix = Translate(-SKY_LENGTH / 2, SKY_HEIGHT, SKY_LENGTH / 2);
		RenderMesh(meshes["sky_top"], shaders["VertexColor"], modelMatrix);
	}

	{
		modelMatrix = Translate(-SKY_LENGTH / 2, 0, SKY_LENGTH / 2);
		modelMatrix *= RotateOY(M_PI_2);
		RenderMesh(meshes["sky_side"], shaders["VertexColor"], modelMatrix);

		modelMatrix = Translate(-SKY_LENGTH / 2, SKY_HEIGHT, SKY_LENGTH / 2);
		modelMatrix *= RotateOY(M_PI_2);
		RenderMesh(meshes["sky_top"], shaders["VertexColor"], modelMatrix);
	}


	modelMatrix = Translate(-SKY_LENGTH / 2, SKY_HEIGHT + SKY_LENGTH, -SKY_LENGTH / 2);
	modelMatrix *= RotateOX(M_PI_2);
	RenderMesh(meshes["sky_top"], shaders["VertexColor"], modelMatrix);
}

void CarRace::RenderTrees()
{
	/*modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(23, -.89, -3));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	modelMatrix *= RotateOY(3 * M_PI_4);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(19.5, -.89, -4.5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	modelMatrix *= RotateOY(3 * M_PI_4 - .3);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(14.5, -.89, -2));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	modelMatrix *= RotateOY(3 * M_PI_4);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(19.5, .24, -4.8));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["dark_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(18, .24, -4.5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["light_tree"], shaders["Simple"], modelMatrix);*/

	//modelMatrix = glm::mat4(1);
	//modelMatrix = glm::translate(modelMatrix, glm::vec3(17, .24, -4.8));
	//modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	//RenderMesh(meshes["light_tree"], shaders["Simple"], modelMatrix);

	/*modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(20, -.89, 2));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	modelMatrix *= RotateOY(3 * M_PI_4);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(17, -.89, 1));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	modelMatrix *= RotateOY(3 * M_PI_4);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(20.8, -.89, 6.5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	modelMatrix *= RotateOY(.6);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(17.3, .24, 5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["dark_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(21.5, -.89, 11.7));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(25, -.89, 12));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(21.2, -.89, 14.7));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	modelMatrix *= RotateOY(M_PI_2 - .5);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);*/

	/*modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(18, -.89, 11));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	modelMatrix *= RotateOY(-3.5);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(9, -.89, -.58));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	modelMatrix *= RotateOY(M_PI_2 + 1.3);
	modelMatrix *= RotateOY(M_PI_2);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(6, -.89, -3.5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	modelMatrix *= RotateOY(-.5);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(2.6, -.89, -7));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(4, .24, -7.5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["light_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(2, -.89, -2.7));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.5, .24, -7.5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["dark_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, .24, -6));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["light_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-2.5, .24, -5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["dark_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-3.5, .24, -4.5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["light_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5, .24, -6.5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["light_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5, .24, -5.5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["dark_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.5, .24, -5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["light_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, -.89, -2.7));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-4, -.89, .5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, -.89, 2));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.5, -.89, 6));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.1, -.89, 11));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-7.5, -.89, -.7));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-10.6, -.89, -6));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-5.5, .24, -3.6));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["light_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-7, .24, -4));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["dark_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-8.5, .24, -5));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["light_tree"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-11.5, -.89, 1));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	modelMatrix *= RotateOY(-M_PI_4);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-16, -.89, 4));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	modelMatrix *= RotateOY(-M_PI_4);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-17.5, -.89, 9));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	modelMatrix *= RotateOY(-M_PI_4 + .8);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);*/

	// ------ EXTERIOR TRACK ------

	/*modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0, -.89, -14));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-3, -.89, -12));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(-5, -.89, -9));
	modelMatrix = glm::scale(modelMatrix, SCALE_TREE);
	RenderMesh(meshes["green_forest"], shaders["Simple"], modelMatrix)*/;
}

void CarRace::RenderObstacles()
{
	// obstacle1
	obstaclePosition1 = obstaclePath1[obstaclePosIdx1];
	obstaclePosIdx1 = (obstaclePosIdx1 + OBSTACLE_SPEED_1) % obstaclePath1.size();
	currPathPoint = obstaclePosition1;
	nextPathPoint = obstaclePath1[obstaclePosIdx1];

	if (nextPathPoint.z > currPathPoint.z) {
		dir = glm::normalize(nextPathPoint - currPathPoint);
		angle = glm::angle(AXIS_OX, dir);
	}
	else {
		dir = glm::normalize(currPathPoint - nextPathPoint);
		angle = glm::angle(AXIS_OX, dir) + M_PI;
	}

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, obstaclePosition1);
	modelMatrix = glm::scale(modelMatrix, SCALE_CAR);
	modelMatrix *= RotateOY(angle);
	RenderMesh(meshes["obstacle1"], shaders["Simple"], modelMatrix);


	// obstacle2
	obstaclePosition2 = obstaclePath2[obstaclePosIdx2];
	obstaclePosIdx2 = (obstaclePosIdx2 + OBSTACLE_SPEED_2) % obstaclePath2.size();
	currPathPoint = obstaclePosition2;
	nextPathPoint = obstaclePath2[obstaclePosIdx2];

	if (nextPathPoint.z > currPathPoint.z) {
		dir = glm::normalize(nextPathPoint - currPathPoint);
		angle = glm::angle(AXIS_OX, dir);
	}
	else {
		dir = glm::normalize(currPathPoint - nextPathPoint);
		angle = glm::angle(AXIS_OX, dir) + M_PI;
	}

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, obstaclePosition2);
	modelMatrix = glm::scale(modelMatrix, SCALE_CAR);
	modelMatrix *= RotateOY(angle);
	RenderMesh(meshes["obstacle2"], shaders["Simple"], modelMatrix);


	// obstacle3
	obstaclePosition3 = obstaclePath3[obstaclePosIdx3];
	obstaclePosIdx3 = (obstaclePosIdx3 + OBSTACLE_SPEED_3) % obstaclePath3.size();
	currPathPoint = obstaclePosition3;
	nextPathPoint = obstaclePath3[obstaclePosIdx3];

	if (nextPathPoint.z > currPathPoint.z) {
		dir = glm::normalize(nextPathPoint - currPathPoint);
		angle = glm::angle(AXIS_OX, dir);
	}
	else {
		dir = glm::normalize(currPathPoint - nextPathPoint);
		angle = glm::angle(AXIS_OX, dir) + M_PI;
	}

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, obstaclePosition3);
	modelMatrix = glm::scale(modelMatrix, SCALE_CAR);
	modelMatrix *= RotateOY(angle);
	RenderMesh(meshes["obstacle3"], shaders["Simple"], modelMatrix);
}

void CarRace::RenderEnvironment()
{
	RenderGrass();
	//RenderSky();
	RenderTrees();
	RenderRaceTrack();

	RenderObstacles();
}

void CarRace::RenderPlayer()
{
	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, playerPosition);
	modelMatrix = glm::scale(modelMatrix, SCALE_CAR);
	modelMatrix *= RotateOY(playerAngle);
	RenderMesh(meshes["player"], shaders["Simple"], modelMatrix);
}

bool CarRace::SameSide(glm::vec3 p1, glm::vec3 p2, glm::vec3 a, glm::vec3 b)
{
	glm::vec3 cp1 = glm::cross(b - a, p1 - a);
	glm::vec3 cp2 = glm::cross(b - a, p2 - a);

	if (glm::dot(cp1, cp2) >= 0) {
		return true;
	}

	return false;
}

bool CarRace::PointInTriangle(glm::vec3 p, glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
	if (SameSide(p, a, b, c) && SameSide(p, b, a, c) && SameSide(p, c, a, b)) {
		return true;
	}

	return false;
}

bool CarRace::PlayerIsOnTrack(glm::vec3 playerPos)
{
	glm::vec3 in1, in2, out1, out2;
	glm::vec3 pos = glm::vec3(playerPos.x, 0, playerPos.z);

	for (int i = 0; i < meshes["raceTrack"]->vertices.size() / 2 - 1; i++) {
		in1 = trackInnerVertices[i].position;
		in2 = trackInnerVertices[i + 1].position;
		out1 = trackOuterVertices[i].position;
		out2 = trackOuterVertices[i + 1].position;

		if (PointInTriangle(pos, in1, in2, out1) ||
			PointInTriangle(pos, in2, out1, out2)) {
			return true;
		}
	}

	in1 = trackInnerVertices[trackInnerVertices.size() - 1].position;
	in2 = trackInnerVertices[0].position;
	out1 = trackOuterVertices[trackOuterVertices.size() - 1].position;
	out2 = trackOuterVertices[0].position;

	if (PointInTriangle(pos, in1, in2, out1) ||
		PointInTriangle(pos, in2, out1, out2)) {
		return true;
	}

	return false;
}

bool CarRace::CollidesObstacle(glm::vec3 obstaclePosition)
{
	auto distance = sqrt(
		(playerPosition.x - obstaclePosition.x) * (playerPosition.x - obstaclePosition.x) +
		(playerPosition.y - obstaclePosition.y) * (playerPosition.y - obstaclePosition.y) +
		(playerPosition.z - obstaclePosition.z) * (playerPosition.z - obstaclePosition.z)
	);

	return distance < 2 * CAR_RADIUS;
}

void CarRace::Update(float deltaTimeSeconds)
{
	RenderEnvironment();
	RenderPlayer();

	// Render the camera target. This is useful for understanding where
	// the rotation point is, when moving in third-person camera mode.
	if (renderCameraTarget)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
	}
}


void CarRace::FrameEnd()
{
	DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void CarRace::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// Render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

void CarRace::OnInputUpdate(float deltaTime, int mods)
{
	// move the camera only if MOUSE_RIGHT button is pressed
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		if (window->KeyHold(GLFW_KEY_W)) {
			// Translate the camera forward
			camera->TranslateForward(deltaTime * CAMERA_SPEED);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			// Translate the camera to the left
			camera->TranslateRight(-deltaTime * CAMERA_SPEED);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			// Translate the camera backward
			camera->TranslateForward(-deltaTime * CAMERA_SPEED);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// Translate the camera to the right
			camera->TranslateRight(deltaTime * CAMERA_SPEED);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// Translate the camera downward
			camera->MoveUpward(-deltaTime * CAMERA_SPEED);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			// Translate the camera upward
			camera->MoveUpward(deltaTime * CAMERA_SPEED);
		}
	}
	else {
		if (CollidesObstacle(obstaclePosition1) ||
			CollidesObstacle(obstaclePosition2) ||
			CollidesObstacle(obstaclePosition3)) {
			return;
		}

		if (window->KeyHold(GLFW_KEY_W)) {
			oldCameraPos = camera->position;
			oldPlayerPos = playerPosition;

			//camera->MoveForward(deltaTime * MOVE_SPEED);
			playerPosition.z = camera->GetTargetPosition().z;
			playerPosition.x = camera->GetTargetPosition().x;

			if (!PlayerIsOnTrack(playerPosition)) {
				camera->position = oldCameraPos;
				playerPosition = oldPlayerPos;
			}
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			oldCameraPos = camera->position;
			oldPlayerPos = playerPosition;

			//camera->MoveForward(-deltaTime * MOVE_SPEED);
			playerPosition.z = camera->GetTargetPosition().z;
			playerPosition.x = camera->GetTargetPosition().x;

			if (!PlayerIsOnTrack(playerPosition)) {
				camera->position = oldCameraPos;
				playerPosition = oldPlayerPos;
			}
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			playerAngle += deltaTime * MOVE_SPEED * SENSITIVITY;
			camera->RotateThirdPerson_OY(deltaTime * MOVE_SPEED * SENSITIVITY);
		}
		
		if (window->KeyHold(GLFW_KEY_D)) {
			playerAngle -= deltaTime * MOVE_SPEED * SENSITIVITY;
			camera->RotateThirdPerson_OY(-deltaTime * MOVE_SPEED * SENSITIVITY);
		}
	}

	//if (window->KeyHold(GLFW_KEY_Z)) {
	//    fov += deltaTime;
	//    projectionMatrix = glm::perspective(fov, window->props.aspectRatio, 0.01f, 100.0f);
	//}

	//if (window->KeyHold(GLFW_KEY_X)) {
	//    fov -= deltaTime;
	//    projectionMatrix = glm::perspective(fov, window->props.aspectRatio, 0.01f, 100.0f);
	//}

 /*   if (window->KeyHold(GLFW_KEY_C)) {
		width += deltaTime;
		projectionMatrix = glm::ortho(-1.0f, width, -1.0f, 1.0f, 0.0f, 100.0f);
	}

	if (window->KeyHold(GLFW_KEY_V)) {
		width -= deltaTime;
		projectionMatrix = glm::ortho(width, 1.0f, -1.0f, 1.0f, 0.0f, 100.0f);
	}*/
}


void CarRace::OnKeyPress(int key, int mods)
{
	// Add key press event
	if (key == GLFW_KEY_T)
	{
		renderCameraTarget = !renderCameraTarget;
	}
	////Switch projections
	//if (key == GLFW_KEY_O)
	//{
	//    projectionMatrix = glm::ortho(-1, 1, -1, 1, 0, 100);
	//}
	//if (key == GLFW_KEY_P)
	//{
	//    projectionMatrix = glm::perspective(RADIANS(45), window->props.aspectRatio, 0.01f, 100.0f);
	//}
}


void CarRace::OnKeyRelease(int key, int mods)
{
	// Add key release event
}


void CarRace::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// Add mouse move event

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.002f;
		float sensivityOY = 0.002f;

		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = false;
			camera->RotateFirstPerson_OX(-sensivityOX * deltaY);
			camera->RotateFirstPerson_OY(-sensivityOY * deltaX);
		}

		if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
			renderCameraTarget = true;
			camera->RotateThirdPerson_OX(sensivityOX * -deltaY);
			camera->RotateThirdPerson_OY(sensivityOY * -deltaX);
		}
	}
}


void CarRace::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button press event
}


void CarRace::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// Add mouse button release event
}


void CarRace::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void CarRace::OnWindowResize(int width, int height)
{
}
