; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/lzma_encoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_coder_s = type { %struct.lzma_range_encoder, i32, [4 x i32], [274 x %struct.lzma_match], i32, i32, i8, i8, i8, i32, i32, i32, [16 x [768 x i16]], [12 x [16 x i16]], [12 x i16], [12 x i16], [12 x i16], [12 x i16], [12 x [16 x i16]], [4 x [64 x i16]], [114 x i16], [16 x i16], %struct.lzma_length_encoder, %struct.lzma_length_encoder, [4 x [64 x i32]], [4 x [128 x i32]], i32, i32, [16 x i32], i32, i32, i32, [4096 x %struct.lzma_optimal] }
%struct.lzma_range_encoder = type { i64, i64, i32, i8, i64, i64, [58 x i32], [58 x i16*] }
%struct.lzma_match = type { i32, i32 }
%struct.lzma_length_encoder = type { i16, i16, [16 x [8 x i16]], [16 x [8 x i16]], [256 x i16], [16 x [272 x i32]], i32, [16 x i32] }
%struct.lzma_optimal = type { i32, i8, i8, i32, i32, i32, i32, i32, [4 x i32] }
%struct.lzma_mf_s = type { i8*, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32 (%struct.lzma_mf_s*, %struct.lzma_match*)*, void (%struct.lzma_mf_s*, i32)*, i32*, i32*, i32, i32, i32, i32, i32, i32, i32, i32, i32 }
%struct.lzma_options_lzma = type { i32, i8*, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i8*, i8* }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_lz_options = type { i64, i64, i64, i64, i64, i32, i32, i8*, i32 }
%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_filter_info_s = type { i64, {}*, i8* }
%struct.lzma_lz_encoder = type { %struct.lzma_coder_s*, i32 (%struct.lzma_coder_s*, %struct.lzma_mf_s*, i8*, i64*, i64)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*, %struct.lzma_filter*)* }

@.str = private unnamed_addr constant [23 x i8] c"limit == (4294967295U)\00", align 1
@.str.1 = private unnamed_addr constant [82 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/lzma_encoder.c\00", align 1
@__PRETTY_FUNCTION__.lzma_lzma_encode = private unnamed_addr constant [122 x i8] c"lzma_ret lzma_lzma_encode(lzma_coder *restrict, lzma_mf *restrict, uint8_t *restrict, size_t *restrict, size_t, uint32_t)\00", align 1
@.str.2 = private unnamed_addr constant [29 x i8] c"*byte <= (4 * 5 + 4) * 9 + 8\00", align 1
@__PRETTY_FUNCTION__.lzma_lzma_lclppb_encode = private unnamed_addr constant [68 x i8] c"_Bool lzma_lzma_lclppb_encode(const lzma_options_lzma *, uint8_t *)\00", align 1
@.str.3 = private unnamed_addr constant [21 x i8] c"mf_position(mf) == 0\00", align 1
@__PRETTY_FUNCTION__.encode_init = private unnamed_addr constant [43 x i8] c"_Bool encode_init(lzma_coder *, lzma_mf *)\00", align 1
@.str.4 = private unnamed_addr constant [30 x i8] c"mf->write_pos == mf->read_pos\00", align 1
@.str.5 = private unnamed_addr constant [26 x i8] c"mf->action == LZMA_FINISH\00", align 1
@.str.6 = private unnamed_addr constant [16 x i8] c"rc->count <= 58\00", align 1
@.str.7 = private unnamed_addr constant [89 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/rangecoder/range_encoder.h\00", align 1
@__PRETTY_FUNCTION__.rc_encode = private unnamed_addr constant [67 x i8] c"_Bool rc_encode(lzma_range_encoder *, uint8_t *, size_t *, size_t)\00", align 1
@.str.8 = private unnamed_addr constant [2 x i8] c"0\00", align 1
@.str.9 = private unnamed_addr constant [9 x i8] c"len == 1\00", align 1
@__PRETTY_FUNCTION__.encode_symbol = private unnamed_addr constant [74 x i8] c"void encode_symbol(lzma_coder *, lzma_mf *, uint32_t, uint32_t, uint32_t)\00", align 1
@.str.10 = private unnamed_addr constant [22 x i8] c"mf->read_ahead >= len\00", align 1
@.str.11 = private unnamed_addr constant [50 x i8] c"len <= (2 + ((1 << 3) + (1 << 3) + (1 << 8)) - 1)\00", align 1
@__PRETTY_FUNCTION__.length = private unnamed_addr constant [96 x i8] c"void length(lzma_range_encoder *, lzma_length_encoder *, const uint32_t, uint32_t, const _Bool)\00", align 1
@lzma_rc_prices = external constant [128 x i8], align 16
@lzma_fastpos = external constant [8192 x i8], align 16
@.str.12 = private unnamed_addr constant [13 x i8] c"lc + lp <= 4\00", align 1
@.str.13 = private unnamed_addr constant [81 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/lzma_common.h\00", align 1
@__PRETTY_FUNCTION__.literal_init = private unnamed_addr constant [60 x i8] c"void literal_init(probability (*)[768], uint32_t, uint32_t)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @lzma_lzma_encode(%struct.lzma_coder_s* noalias %coder, %struct.lzma_mf_s* noalias %mf, i8* noalias %out, i64* noalias %out_pos, i64 %out_size, i32 %limit) #0 !dbg !101 {
entry:
  %retval = alloca i32, align 4
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  %limit.addr = alloca i32, align 4
  %position = alloca i32, align 4
  %len = alloca i32, align 4
  %back = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !513, metadata !514), !dbg !515
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !516, metadata !514), !dbg !517
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !518, metadata !514), !dbg !519
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !520, metadata !514), !dbg !521
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !522, metadata !514), !dbg !523
  store i32 %limit, i32* %limit.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %limit.addr, metadata !524, metadata !514), !dbg !525
  call void @llvm.dbg.declare(metadata i32* %position, metadata !526, metadata !514), !dbg !527
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !528
  %is_initialized = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 7, !dbg !530
  %1 = load i8, i8* %is_initialized, align 1, !dbg !530
  %tobool = trunc i8 %1 to i1, !dbg !530
  br i1 %tobool, label %if.end, label %land.lhs.true, !dbg !531

land.lhs.true:                                    ; preds = %entry
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !532
  %3 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !534
  %call = call zeroext i1 @encode_init(%struct.lzma_coder_s* %2, %struct.lzma_mf_s* %3), !dbg !535
  br i1 %call, label %if.end, label %if.then, !dbg !536

if.then:                                          ; preds = %land.lhs.true
  store i32 0, i32* %retval, align 4, !dbg !537
  br label %return, !dbg !537

if.end:                                           ; preds = %land.lhs.true, %entry
  %4 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !538
  %call1 = call i32 @mf_position(%struct.lzma_mf_s* %4), !dbg !539
  store i32 %call1, i32* %position, align 4, !dbg !540
  br label %while.body, !dbg !541

while.body:                                       ; preds = %if.end, %if.end26
  call void @llvm.dbg.declare(metadata i32* %len, metadata !542, metadata !514), !dbg !544
  call void @llvm.dbg.declare(metadata i32* %back, metadata !545, metadata !514), !dbg !546
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !547
  %rc = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 0, !dbg !549
  %6 = load i8*, i8** %out.addr, align 8, !dbg !550
  %7 = load i64*, i64** %out_pos.addr, align 8, !dbg !551
  %8 = load i64, i64* %out_size.addr, align 8, !dbg !552
  %call2 = call zeroext i1 @rc_encode(%struct.lzma_range_encoder* %rc, i8* %6, i64* %7, i64 %8), !dbg !553
  br i1 %call2, label %if.then3, label %if.end4, !dbg !554

if.then3:                                         ; preds = %while.body
  %9 = load i32, i32* %limit.addr, align 4, !dbg !555
  %cmp = icmp eq i32 %9, -1, !dbg !555
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !555

cond.true:                                        ; preds = %if.then3
  br label %cond.end, !dbg !557

cond.false:                                       ; preds = %if.then3
  call void @__assert_fail(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([82 x i8], [82 x i8]* @.str.1, i32 0, i32 0), i32 345, i8* getelementptr inbounds ([122 x i8], [122 x i8]* @__PRETTY_FUNCTION__.lzma_lzma_encode, i32 0, i32 0)) #6, !dbg !559
  unreachable, !dbg !559
                                                  ; No predecessors!
  br label %cond.end, !dbg !561

cond.end:                                         ; preds = %10, %cond.true
  store i32 0, i32* %retval, align 4, !dbg !563
  br label %return, !dbg !563

if.end4:                                          ; preds = %while.body
  %11 = load i32, i32* %limit.addr, align 4, !dbg !564
  %cmp5 = icmp ne i32 %11, -1, !dbg !566
  br i1 %cmp5, label %land.lhs.true6, label %if.end12, !dbg !567

land.lhs.true6:                                   ; preds = %if.end4
  %12 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !568
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %12, i32 0, i32 5, !dbg !570
  %13 = load i32, i32* %read_pos, align 8, !dbg !570
  %14 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !571
  %read_ahead = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %14, i32 0, i32 6, !dbg !572
  %15 = load i32, i32* %read_ahead, align 4, !dbg !572
  %sub = sub i32 %13, %15, !dbg !573
  %16 = load i32, i32* %limit.addr, align 4, !dbg !574
  %cmp7 = icmp uge i32 %sub, %16, !dbg !575
  br i1 %cmp7, label %if.then11, label %lor.lhs.false, !dbg !576

lor.lhs.false:                                    ; preds = %land.lhs.true6
  %17 = load i64*, i64** %out_pos.addr, align 8, !dbg !577
  %18 = load i64, i64* %17, align 8, !dbg !578
  %19 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !579
  %rc8 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %19, i32 0, i32 0, !dbg !580
  %call9 = call i64 @rc_pending(%struct.lzma_range_encoder* %rc8), !dbg !581
  %add = add i64 %18, %call9, !dbg !582
  %cmp10 = icmp uge i64 %add, 61439, !dbg !583
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !584

if.then11:                                        ; preds = %lor.lhs.false, %land.lhs.true6
  br label %while.end, !dbg !586

if.end12:                                         ; preds = %lor.lhs.false, %if.end4
  %20 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !587
  %read_pos13 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %20, i32 0, i32 5, !dbg !589
  %21 = load i32, i32* %read_pos13, align 8, !dbg !589
  %22 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !590
  %read_limit = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %22, i32 0, i32 7, !dbg !591
  %23 = load i32, i32* %read_limit, align 8, !dbg !591
  %cmp14 = icmp uge i32 %21, %23, !dbg !592
  br i1 %cmp14, label %if.then15, label %if.end23, !dbg !593

if.then15:                                        ; preds = %if.end12
  %24 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !594
  %action = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %24, i32 0, i32 20, !dbg !597
  %25 = load i32, i32* %action, align 8, !dbg !597
  %cmp16 = icmp eq i32 %25, 0, !dbg !598
  br i1 %cmp16, label %if.then17, label %if.end18, !dbg !599

if.then17:                                        ; preds = %if.then15
  store i32 0, i32* %retval, align 4, !dbg !600
  br label %return, !dbg !600

if.end18:                                         ; preds = %if.then15
  %26 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !601
  %read_ahead19 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %26, i32 0, i32 6, !dbg !603
  %27 = load i32, i32* %read_ahead19, align 4, !dbg !603
  %cmp20 = icmp eq i32 %27, 0, !dbg !604
  br i1 %cmp20, label %if.then21, label %if.end22, !dbg !605

if.then21:                                        ; preds = %if.end18
  br label %while.end, !dbg !606

if.end22:                                         ; preds = %if.end18
  br label %if.end23, !dbg !607

if.end23:                                         ; preds = %if.end22, %if.end12
  %28 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !608
  %fast_mode = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %28, i32 0, i32 6, !dbg !610
  %29 = load i8, i8* %fast_mode, align 4, !dbg !610
  %tobool24 = trunc i8 %29 to i1, !dbg !610
  br i1 %tobool24, label %if.then25, label %if.else, !dbg !611

if.then25:                                        ; preds = %if.end23
  %30 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !612
  %31 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !613
  call void @lzma_lzma_optimum_fast(%struct.lzma_coder_s* %30, %struct.lzma_mf_s* %31, i32* %back, i32* %len), !dbg !614
  br label %if.end26, !dbg !614

if.else:                                          ; preds = %if.end23
  %32 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !615
  %33 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !616
  %34 = load i32, i32* %position, align 4, !dbg !617
  call void @lzma_lzma_optimum_normal(%struct.lzma_coder_s* %32, %struct.lzma_mf_s* %33, i32* %back, i32* %len, i32 %34), !dbg !618
  br label %if.end26

if.end26:                                         ; preds = %if.else, %if.then25
  %35 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !619
  %36 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !620
  %37 = load i32, i32* %back, align 4, !dbg !621
  %38 = load i32, i32* %len, align 4, !dbg !622
  %39 = load i32, i32* %position, align 4, !dbg !623
  call void @encode_symbol(%struct.lzma_coder_s* %35, %struct.lzma_mf_s* %36, i32 %37, i32 %38, i32 %39), !dbg !624
  %40 = load i32, i32* %len, align 4, !dbg !625
  %41 = load i32, i32* %position, align 4, !dbg !626
  %add27 = add i32 %41, %40, !dbg !626
  store i32 %add27, i32* %position, align 4, !dbg !626
  br label %while.body, !dbg !627

while.end:                                        ; preds = %if.then21, %if.then11
  %42 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !629
  %is_flushed = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %42, i32 0, i32 8, !dbg !631
  %43 = load i8, i8* %is_flushed, align 2, !dbg !631
  %tobool28 = trunc i8 %43 to i1, !dbg !631
  br i1 %tobool28, label %if.end43, label %if.then29, !dbg !632

if.then29:                                        ; preds = %while.end
  %44 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !633
  %is_flushed30 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %44, i32 0, i32 8, !dbg !635
  store i8 1, i8* %is_flushed30, align 2, !dbg !636
  %45 = load i32, i32* %limit.addr, align 4, !dbg !637
  %cmp31 = icmp eq i32 %45, -1, !dbg !639
  br i1 %cmp31, label %if.then32, label %if.end33, !dbg !640

if.then32:                                        ; preds = %if.then29
  %46 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !641
  %47 = load i32, i32* %position, align 4, !dbg !642
  call void @encode_eopm(%struct.lzma_coder_s* %46, i32 %47), !dbg !643
  br label %if.end33, !dbg !643

if.end33:                                         ; preds = %if.then32, %if.then29
  %48 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !644
  %rc34 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %48, i32 0, i32 0, !dbg !645
  call void @rc_flush(%struct.lzma_range_encoder* %rc34), !dbg !646
  %49 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !647
  %rc35 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %49, i32 0, i32 0, !dbg !649
  %50 = load i8*, i8** %out.addr, align 8, !dbg !650
  %51 = load i64*, i64** %out_pos.addr, align 8, !dbg !651
  %52 = load i64, i64* %out_size.addr, align 8, !dbg !652
  %call36 = call zeroext i1 @rc_encode(%struct.lzma_range_encoder* %rc35, i8* %50, i64* %51, i64 %52), !dbg !653
  br i1 %call36, label %if.then37, label %if.end42, !dbg !654

if.then37:                                        ; preds = %if.end33
  %53 = load i32, i32* %limit.addr, align 4, !dbg !655
  %cmp38 = icmp eq i32 %53, -1, !dbg !655
  br i1 %cmp38, label %cond.true39, label %cond.false40, !dbg !655

cond.true39:                                      ; preds = %if.then37
  br label %cond.end41, !dbg !657

cond.false40:                                     ; preds = %if.then37
  call void @__assert_fail(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([82 x i8], [82 x i8]* @.str.1, i32 0, i32 0), i32 404, i8* getelementptr inbounds ([122 x i8], [122 x i8]* @__PRETTY_FUNCTION__.lzma_lzma_encode, i32 0, i32 0)) #6, !dbg !659
  unreachable, !dbg !659
                                                  ; No predecessors!
  br label %cond.end41, !dbg !661

cond.end41:                                       ; preds = %54, %cond.true39
  store i32 0, i32* %retval, align 4, !dbg !663
  br label %return, !dbg !663

if.end42:                                         ; preds = %if.end33
  br label %if.end43, !dbg !664

if.end43:                                         ; preds = %if.end42, %while.end
  %55 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !665
  %is_flushed44 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %55, i32 0, i32 8, !dbg !666
  store i8 0, i8* %is_flushed44, align 2, !dbg !667
  store i32 1, i32* %retval, align 4, !dbg !668
  br label %return, !dbg !668

return:                                           ; preds = %if.end43, %cond.end41, %if.then17, %cond.end, %if.then
  %56 = load i32, i32* %retval, align 4, !dbg !669
  ret i32 %56, !dbg !669
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal zeroext i1 @encode_init(%struct.lzma_coder_s* %coder, %struct.lzma_mf_s* %mf) #0 !dbg !398 {
entry:
  %retval = alloca i1, align 1
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !670, metadata !514), !dbg !671
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !672, metadata !514), !dbg !673
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !674
  %call = call i32 @mf_position(%struct.lzma_mf_s* %0), !dbg !674
  %cmp = icmp eq i32 %call, 0, !dbg !674
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !674

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !675

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([82 x i8], [82 x i8]* @.str.1, i32 0, i32 0), i32 279, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @__PRETTY_FUNCTION__.encode_init, i32 0, i32 0)) #6, !dbg !677
  unreachable, !dbg !677
                                                  ; No predecessors!
  br label %cond.end, !dbg !679

cond.end:                                         ; preds = %1, %cond.true
  %2 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !681
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %2, i32 0, i32 5, !dbg !683
  %3 = load i32, i32* %read_pos, align 8, !dbg !683
  %4 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !684
  %read_limit = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %4, i32 0, i32 7, !dbg !685
  %5 = load i32, i32* %read_limit, align 8, !dbg !685
  %cmp1 = icmp eq i32 %3, %5, !dbg !686
  br i1 %cmp1, label %if.then, label %if.else, !dbg !687

if.then:                                          ; preds = %cond.end
  %6 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !688
  %action = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %6, i32 0, i32 20, !dbg !691
  %7 = load i32, i32* %action, align 8, !dbg !691
  %cmp2 = icmp eq i32 %7, 0, !dbg !692
  br i1 %cmp2, label %if.then3, label %if.end, !dbg !693

if.then3:                                         ; preds = %if.then
  store i1 false, i1* %retval, align 1, !dbg !694
  br label %return, !dbg !694

if.end:                                           ; preds = %if.then
  %8 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !695
  %write_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %8, i32 0, i32 8, !dbg !695
  %9 = load i32, i32* %write_pos, align 4, !dbg !695
  %10 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !695
  %read_pos4 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %10, i32 0, i32 5, !dbg !695
  %11 = load i32, i32* %read_pos4, align 8, !dbg !695
  %cmp5 = icmp eq i32 %9, %11, !dbg !695
  br i1 %cmp5, label %cond.true6, label %cond.false7, !dbg !695

cond.true6:                                       ; preds = %if.end
  br label %cond.end8, !dbg !696

cond.false7:                                      ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([82 x i8], [82 x i8]* @.str.1, i32 0, i32 0), i32 286, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @__PRETTY_FUNCTION__.encode_init, i32 0, i32 0)) #6, !dbg !698
  unreachable, !dbg !698
                                                  ; No predecessors!
  br label %cond.end8, !dbg !700

cond.end8:                                        ; preds = %12, %cond.true6
  %13 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !702
  %action9 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %13, i32 0, i32 20, !dbg !702
  %14 = load i32, i32* %action9, align 8, !dbg !702
  %cmp10 = icmp eq i32 %14, 3, !dbg !702
  br i1 %cmp10, label %cond.true11, label %cond.false12, !dbg !702

cond.true11:                                      ; preds = %cond.end8
  br label %cond.end13, !dbg !703

cond.false12:                                     ; preds = %cond.end8
  call void @__assert_fail(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([82 x i8], [82 x i8]* @.str.1, i32 0, i32 0), i32 287, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @__PRETTY_FUNCTION__.encode_init, i32 0, i32 0)) #6, !dbg !704
  unreachable, !dbg !704
                                                  ; No predecessors!
  br label %cond.end13, !dbg !705

cond.end13:                                       ; preds = %15, %cond.true11
  br label %if.end18, !dbg !706

if.else:                                          ; preds = %cond.end
  %16 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !707
  call void @mf_skip(%struct.lzma_mf_s* %16, i32 1), !dbg !709
  %17 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !710
  %read_ahead = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %17, i32 0, i32 6, !dbg !711
  store i32 0, i32* %read_ahead, align 4, !dbg !712
  %18 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !713
  %rc = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %18, i32 0, i32 0, !dbg !714
  %19 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !715
  %is_match = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %19, i32 0, i32 13, !dbg !716
  %arrayidx = getelementptr inbounds [12 x [16 x i16]], [12 x [16 x i16]]* %is_match, i64 0, i64 0, !dbg !715
  %arrayidx14 = getelementptr inbounds [16 x i16], [16 x i16]* %arrayidx, i64 0, i64 0, !dbg !715
  call void @rc_bit(%struct.lzma_range_encoder* %rc, i16* %arrayidx14, i32 0), !dbg !717
  %20 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !718
  %rc15 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %20, i32 0, i32 0, !dbg !719
  %21 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !720
  %literal = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %21, i32 0, i32 12, !dbg !721
  %arrayidx16 = getelementptr inbounds [16 x [768 x i16]], [16 x [768 x i16]]* %literal, i64 0, i64 0, !dbg !720
  %arraydecay = getelementptr inbounds [768 x i16], [768 x i16]* %arrayidx16, i32 0, i32 0, !dbg !720
  %22 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !722
  %buffer = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %22, i32 0, i32 0, !dbg !723
  %23 = load i8*, i8** %buffer, align 8, !dbg !723
  %arrayidx17 = getelementptr inbounds i8, i8* %23, i64 0, !dbg !722
  %24 = load i8, i8* %arrayidx17, align 1, !dbg !722
  %conv = zext i8 %24 to i32, !dbg !722
  call void @rc_bittree(%struct.lzma_range_encoder* %rc15, i16* %arraydecay, i32 8, i32 %conv), !dbg !724
  br label %if.end18

if.end18:                                         ; preds = %if.else, %cond.end13
  %25 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !725
  %is_initialized = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %25, i32 0, i32 7, !dbg !726
  store i8 1, i8* %is_initialized, align 1, !dbg !727
  store i1 true, i1* %retval, align 1, !dbg !728
  br label %return, !dbg !728

return:                                           ; preds = %if.end18, %if.then3
  %26 = load i1, i1* %retval, align 1, !dbg !729
  ret i1 %26, !dbg !729
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @mf_position(%struct.lzma_mf_s* %mf) #2 !dbg !409 {
entry:
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !730, metadata !514), !dbg !731
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !732
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %0, i32 0, i32 5, !dbg !733
  %1 = load i32, i32* %read_pos, align 8, !dbg !733
  %2 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !734
  %read_ahead = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %2, i32 0, i32 6, !dbg !735
  %3 = load i32, i32* %read_ahead, align 4, !dbg !735
  %sub = sub i32 %1, %3, !dbg !736
  ret i32 %sub, !dbg !737
}

; Function Attrs: inlinehint nounwind uwtable
define internal zeroext i1 @rc_encode(%struct.lzma_range_encoder* %rc, i8* %out, i64* %out_pos, i64 %out_size) #2 !dbg !414 {
entry:
  %retval = alloca i1, align 1
  %rc.addr = alloca %struct.lzma_range_encoder*, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  %prob = alloca i16, align 2
  %prob20 = alloca i16, align 2
  %bound = alloca i32, align 4
  store %struct.lzma_range_encoder* %rc, %struct.lzma_range_encoder** %rc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_range_encoder** %rc.addr, metadata !738, metadata !514), !dbg !739
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !740, metadata !514), !dbg !741
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !742, metadata !514), !dbg !743
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !744, metadata !514), !dbg !745
  %0 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !746
  %count = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %0, i32 0, i32 4, !dbg !746
  %1 = load i64, i64* %count, align 8, !dbg !746
  %cmp = icmp ule i64 %1, 58, !dbg !746
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !746

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !747

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([89 x i8], [89 x i8]* @.str.7, i32 0, i32 0), i32 154, i8* getelementptr inbounds ([67 x i8], [67 x i8]* @__PRETTY_FUNCTION__.rc_encode, i32 0, i32 0)) #6, !dbg !749
  unreachable, !dbg !749
                                                  ; No predecessors!
  br label %cond.end, !dbg !751

cond.end:                                         ; preds = %2, %cond.true
  br label %while.cond, !dbg !753

while.cond:                                       ; preds = %sw.epilog, %cond.end
  %3 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !754
  %pos = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %3, i32 0, i32 5, !dbg !755
  %4 = load i64, i64* %pos, align 8, !dbg !755
  %5 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !756
  %count1 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %5, i32 0, i32 4, !dbg !757
  %6 = load i64, i64* %count1, align 8, !dbg !757
  %cmp2 = icmp ult i64 %4, %6, !dbg !758
  br i1 %cmp2, label %while.body, label %while.end, !dbg !759

while.body:                                       ; preds = %while.cond
  %7 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !760
  %range = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %7, i32 0, i32 2, !dbg !763
  %8 = load i32, i32* %range, align 8, !dbg !763
  %cmp3 = icmp ult i32 %8, 16777216, !dbg !764
  br i1 %cmp3, label %if.then, label %if.end6, !dbg !765

if.then:                                          ; preds = %while.body
  %9 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !766
  %10 = load i8*, i8** %out.addr, align 8, !dbg !769
  %11 = load i64*, i64** %out_pos.addr, align 8, !dbg !770
  %12 = load i64, i64* %out_size.addr, align 8, !dbg !771
  %call = call zeroext i1 @rc_shift_low(%struct.lzma_range_encoder* %9, i8* %10, i64* %11, i64 %12), !dbg !772
  br i1 %call, label %if.then4, label %if.end, !dbg !773

if.then4:                                         ; preds = %if.then
  store i1 true, i1* %retval, align 1, !dbg !774
  br label %return, !dbg !774

if.end:                                           ; preds = %if.then
  %13 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !775
  %range5 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %13, i32 0, i32 2, !dbg !776
  %14 = load i32, i32* %range5, align 8, !dbg !777
  %shl = shl i32 %14, 8, !dbg !777
  store i32 %shl, i32* %range5, align 8, !dbg !777
  br label %if.end6, !dbg !778

if.end6:                                          ; preds = %if.end, %while.body
  %15 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !779
  %pos7 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %15, i32 0, i32 5, !dbg !780
  %16 = load i64, i64* %pos7, align 8, !dbg !780
  %17 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !781
  %symbols = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %17, i32 0, i32 6, !dbg !782
  %arrayidx = getelementptr inbounds [58 x i32], [58 x i32]* %symbols, i64 0, i64 %16, !dbg !781
  %18 = load i32, i32* %arrayidx, align 4, !dbg !781
  switch i32 %18, label %sw.default [
    i32 0, label %sw.bb
    i32 1, label %sw.bb19
    i32 2, label %sw.bb40
    i32 3, label %sw.bb43
    i32 4, label %sw.bb50
  ], !dbg !783

sw.bb:                                            ; preds = %if.end6
  call void @llvm.dbg.declare(metadata i16* %prob, metadata !784, metadata !514), !dbg !787
  %19 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !788
  %pos8 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %19, i32 0, i32 5, !dbg !789
  %20 = load i64, i64* %pos8, align 8, !dbg !789
  %21 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !790
  %probs = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %21, i32 0, i32 7, !dbg !791
  %arrayidx9 = getelementptr inbounds [58 x i16*], [58 x i16*]* %probs, i64 0, i64 %20, !dbg !790
  %22 = load i16*, i16** %arrayidx9, align 8, !dbg !790
  %23 = load i16, i16* %22, align 2, !dbg !792
  store i16 %23, i16* %prob, align 2, !dbg !787
  %24 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !793
  %range10 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %24, i32 0, i32 2, !dbg !794
  %25 = load i32, i32* %range10, align 8, !dbg !794
  %shr = lshr i32 %25, 11, !dbg !795
  %26 = load i16, i16* %prob, align 2, !dbg !796
  %conv = zext i16 %26 to i32, !dbg !796
  %mul = mul i32 %shr, %conv, !dbg !797
  %27 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !798
  %range11 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %27, i32 0, i32 2, !dbg !799
  store i32 %mul, i32* %range11, align 8, !dbg !800
  %28 = load i16, i16* %prob, align 2, !dbg !801
  %conv12 = zext i16 %28 to i32, !dbg !801
  %sub = sub i32 2048, %conv12, !dbg !802
  %shr13 = lshr i32 %sub, 5, !dbg !803
  %29 = load i16, i16* %prob, align 2, !dbg !804
  %conv14 = zext i16 %29 to i32, !dbg !804
  %add = add i32 %conv14, %shr13, !dbg !804
  %conv15 = trunc i32 %add to i16, !dbg !804
  store i16 %conv15, i16* %prob, align 2, !dbg !804
  %30 = load i16, i16* %prob, align 2, !dbg !805
  %31 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !806
  %pos16 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %31, i32 0, i32 5, !dbg !807
  %32 = load i64, i64* %pos16, align 8, !dbg !807
  %33 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !808
  %probs17 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %33, i32 0, i32 7, !dbg !809
  %arrayidx18 = getelementptr inbounds [58 x i16*], [58 x i16*]* %probs17, i64 0, i64 %32, !dbg !808
  %34 = load i16*, i16** %arrayidx18, align 8, !dbg !808
  store i16 %30, i16* %34, align 2, !dbg !810
  br label %sw.epilog, !dbg !811

sw.bb19:                                          ; preds = %if.end6
  call void @llvm.dbg.declare(metadata i16* %prob20, metadata !812, metadata !514), !dbg !814
  %35 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !815
  %pos21 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %35, i32 0, i32 5, !dbg !816
  %36 = load i64, i64* %pos21, align 8, !dbg !816
  %37 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !817
  %probs22 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %37, i32 0, i32 7, !dbg !818
  %arrayidx23 = getelementptr inbounds [58 x i16*], [58 x i16*]* %probs22, i64 0, i64 %36, !dbg !817
  %38 = load i16*, i16** %arrayidx23, align 8, !dbg !817
  %39 = load i16, i16* %38, align 2, !dbg !819
  store i16 %39, i16* %prob20, align 2, !dbg !814
  call void @llvm.dbg.declare(metadata i32* %bound, metadata !820, metadata !514), !dbg !821
  %40 = load i16, i16* %prob20, align 2, !dbg !822
  %conv24 = zext i16 %40 to i32, !dbg !822
  %41 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !823
  %range25 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %41, i32 0, i32 2, !dbg !824
  %42 = load i32, i32* %range25, align 8, !dbg !824
  %shr26 = lshr i32 %42, 11, !dbg !825
  %mul27 = mul i32 %conv24, %shr26, !dbg !826
  store i32 %mul27, i32* %bound, align 4, !dbg !821
  %43 = load i32, i32* %bound, align 4, !dbg !827
  %conv28 = zext i32 %43 to i64, !dbg !827
  %44 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !828
  %low = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %44, i32 0, i32 0, !dbg !829
  %45 = load i64, i64* %low, align 8, !dbg !830
  %add29 = add i64 %45, %conv28, !dbg !830
  store i64 %add29, i64* %low, align 8, !dbg !830
  %46 = load i32, i32* %bound, align 4, !dbg !831
  %47 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !832
  %range30 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %47, i32 0, i32 2, !dbg !833
  %48 = load i32, i32* %range30, align 8, !dbg !834
  %sub31 = sub i32 %48, %46, !dbg !834
  store i32 %sub31, i32* %range30, align 8, !dbg !834
  %49 = load i16, i16* %prob20, align 2, !dbg !835
  %conv32 = zext i16 %49 to i32, !dbg !835
  %shr33 = ashr i32 %conv32, 5, !dbg !836
  %50 = load i16, i16* %prob20, align 2, !dbg !837
  %conv34 = zext i16 %50 to i32, !dbg !837
  %sub35 = sub nsw i32 %conv34, %shr33, !dbg !837
  %conv36 = trunc i32 %sub35 to i16, !dbg !837
  store i16 %conv36, i16* %prob20, align 2, !dbg !837
  %51 = load i16, i16* %prob20, align 2, !dbg !838
  %52 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !839
  %pos37 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %52, i32 0, i32 5, !dbg !840
  %53 = load i64, i64* %pos37, align 8, !dbg !840
  %54 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !841
  %probs38 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %54, i32 0, i32 7, !dbg !842
  %arrayidx39 = getelementptr inbounds [58 x i16*], [58 x i16*]* %probs38, i64 0, i64 %53, !dbg !841
  %55 = load i16*, i16** %arrayidx39, align 8, !dbg !841
  store i16 %51, i16* %55, align 2, !dbg !843
  br label %sw.epilog, !dbg !844

sw.bb40:                                          ; preds = %if.end6
  %56 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !845
  %range41 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %56, i32 0, i32 2, !dbg !846
  %57 = load i32, i32* %range41, align 8, !dbg !847
  %shr42 = lshr i32 %57, 1, !dbg !847
  store i32 %shr42, i32* %range41, align 8, !dbg !847
  br label %sw.epilog, !dbg !848

sw.bb43:                                          ; preds = %if.end6
  %58 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !849
  %range44 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %58, i32 0, i32 2, !dbg !850
  %59 = load i32, i32* %range44, align 8, !dbg !851
  %shr45 = lshr i32 %59, 1, !dbg !851
  store i32 %shr45, i32* %range44, align 8, !dbg !851
  %60 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !852
  %range46 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %60, i32 0, i32 2, !dbg !853
  %61 = load i32, i32* %range46, align 8, !dbg !853
  %conv47 = zext i32 %61 to i64, !dbg !852
  %62 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !854
  %low48 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %62, i32 0, i32 0, !dbg !855
  %63 = load i64, i64* %low48, align 8, !dbg !856
  %add49 = add i64 %63, %conv47, !dbg !856
  store i64 %add49, i64* %low48, align 8, !dbg !856
  br label %sw.epilog, !dbg !857

sw.bb50:                                          ; preds = %if.end6
  %64 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !858
  %range51 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %64, i32 0, i32 2, !dbg !859
  store i32 -1, i32* %range51, align 8, !dbg !860
  br label %do.body, !dbg !861

do.body:                                          ; preds = %do.cond, %sw.bb50
  %65 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !862
  %66 = load i8*, i8** %out.addr, align 8, !dbg !865
  %67 = load i64*, i64** %out_pos.addr, align 8, !dbg !866
  %68 = load i64, i64* %out_size.addr, align 8, !dbg !867
  %call52 = call zeroext i1 @rc_shift_low(%struct.lzma_range_encoder* %65, i8* %66, i64* %67, i64 %68), !dbg !868
  br i1 %call52, label %if.then53, label %if.end54, !dbg !869

if.then53:                                        ; preds = %do.body
  store i1 true, i1* %retval, align 1, !dbg !870
  br label %return, !dbg !870

if.end54:                                         ; preds = %do.body
  br label %do.cond, !dbg !871

do.cond:                                          ; preds = %if.end54
  %69 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !872
  %pos55 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %69, i32 0, i32 5, !dbg !874
  %70 = load i64, i64* %pos55, align 8, !dbg !875
  %inc = add i64 %70, 1, !dbg !875
  store i64 %inc, i64* %pos55, align 8, !dbg !875
  %71 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !876
  %count56 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %71, i32 0, i32 4, !dbg !877
  %72 = load i64, i64* %count56, align 8, !dbg !877
  %cmp57 = icmp ult i64 %inc, %72, !dbg !878
  br i1 %cmp57, label %do.body, label %do.end, !dbg !879

do.end:                                           ; preds = %do.cond
  %73 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !880
  call void @rc_reset(%struct.lzma_range_encoder* %73), !dbg !881
  store i1 false, i1* %retval, align 1, !dbg !882
  br label %return, !dbg !882

sw.default:                                       ; preds = %if.end6
  call void @__assert_fail(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([89 x i8], [89 x i8]* @.str.7, i32 0, i32 0), i32 212, i8* getelementptr inbounds ([67 x i8], [67 x i8]* @__PRETTY_FUNCTION__.rc_encode, i32 0, i32 0)) #6, !dbg !883
  unreachable, !dbg !883

sw.epilog:                                        ; preds = %sw.bb43, %sw.bb40, %sw.bb19, %sw.bb
  %74 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !884
  %pos59 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %74, i32 0, i32 5, !dbg !885
  %75 = load i64, i64* %pos59, align 8, !dbg !886
  %inc60 = add i64 %75, 1, !dbg !886
  store i64 %inc60, i64* %pos59, align 8, !dbg !886
  br label %while.cond, !dbg !887

while.end:                                        ; preds = %while.cond
  %76 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !888
  %count61 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %76, i32 0, i32 4, !dbg !889
  store i64 0, i64* %count61, align 8, !dbg !890
  %77 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !891
  %pos62 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %77, i32 0, i32 5, !dbg !892
  store i64 0, i64* %pos62, align 8, !dbg !893
  store i1 false, i1* %retval, align 1, !dbg !894
  br label %return, !dbg !894

return:                                           ; preds = %while.end, %do.end, %if.then53, %if.then4
  %78 = load i1, i1* %retval, align 1, !dbg !895
  ret i1 %78, !dbg !895
}

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #3

; Function Attrs: inlinehint nounwind uwtable
define internal i64 @rc_pending(%struct.lzma_range_encoder* %rc) #2 !dbg !418 {
entry:
  %rc.addr = alloca %struct.lzma_range_encoder*, align 8
  store %struct.lzma_range_encoder* %rc, %struct.lzma_range_encoder** %rc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_range_encoder** %rc.addr, metadata !896, metadata !514), !dbg !897
  %0 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !898
  %cache_size = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %0, i32 0, i32 1, !dbg !899
  %1 = load i64, i64* %cache_size, align 8, !dbg !899
  %add = add i64 %1, 5, !dbg !900
  %sub = sub i64 %add, 1, !dbg !901
  ret i64 %sub, !dbg !902
}

declare void @lzma_lzma_optimum_fast(%struct.lzma_coder_s*, %struct.lzma_mf_s*, i32*, i32*) #4

declare void @lzma_lzma_optimum_normal(%struct.lzma_coder_s*, %struct.lzma_mf_s*, i32*, i32*, i32) #4

; Function Attrs: nounwind uwtable
define internal void @encode_symbol(%struct.lzma_coder_s* %coder, %struct.lzma_mf_s* %mf, i32 %back, i32 %len, i32 %position) #0 !dbg !423 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %back.addr = alloca i32, align 4
  %len.addr = alloca i32, align 4
  %position.addr = alloca i32, align 4
  %pos_state = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !903, metadata !514), !dbg !904
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !905, metadata !514), !dbg !906
  store i32 %back, i32* %back.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %back.addr, metadata !907, metadata !514), !dbg !908
  store i32 %len, i32* %len.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len.addr, metadata !909, metadata !514), !dbg !910
  store i32 %position, i32* %position.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %position.addr, metadata !911, metadata !514), !dbg !912
  call void @llvm.dbg.declare(metadata i32* %pos_state, metadata !913, metadata !514), !dbg !914
  %0 = load i32, i32* %position.addr, align 4, !dbg !915
  %1 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !916
  %pos_mask = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %1, i32 0, i32 9, !dbg !917
  %2 = load i32, i32* %pos_mask, align 8, !dbg !917
  %and = and i32 %0, %2, !dbg !918
  store i32 %and, i32* %pos_state, align 4, !dbg !914
  %3 = load i32, i32* %back.addr, align 4, !dbg !919
  %cmp = icmp eq i32 %3, -1, !dbg !921
  br i1 %cmp, label %if.then, label %if.else, !dbg !922

if.then:                                          ; preds = %entry
  %4 = load i32, i32* %len.addr, align 4, !dbg !923
  %cmp1 = icmp eq i32 %4, 1, !dbg !923
  br i1 %cmp1, label %cond.true, label %cond.false, !dbg !923

cond.true:                                        ; preds = %if.then
  br label %cond.end, !dbg !925

cond.false:                                       ; preds = %if.then
  call void @__assert_fail(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.9, i32 0, i32 0), i8* getelementptr inbounds ([82 x i8], [82 x i8]* @.str.1, i32 0, i32 0), i32 250, i8* getelementptr inbounds ([74 x i8], [74 x i8]* @__PRETTY_FUNCTION__.encode_symbol, i32 0, i32 0)) #6, !dbg !927
  unreachable, !dbg !927
                                                  ; No predecessors!
  br label %cond.end, !dbg !929

cond.end:                                         ; preds = %5, %cond.true
  %6 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !931
  %rc = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %6, i32 0, i32 0, !dbg !932
  %7 = load i32, i32* %pos_state, align 4, !dbg !933
  %idxprom = zext i32 %7 to i64, !dbg !934
  %8 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !935
  %state = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %8, i32 0, i32 1, !dbg !936
  %9 = load i32, i32* %state, align 8, !dbg !936
  %idxprom2 = zext i32 %9 to i64, !dbg !934
  %10 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !934
  %is_match = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %10, i32 0, i32 13, !dbg !937
  %arrayidx = getelementptr inbounds [12 x [16 x i16]], [12 x [16 x i16]]* %is_match, i64 0, i64 %idxprom2, !dbg !934
  %arrayidx3 = getelementptr inbounds [16 x i16], [16 x i16]* %arrayidx, i64 0, i64 %idxprom, !dbg !934
  call void @rc_bit(%struct.lzma_range_encoder* %rc, i16* %arrayidx3, i32 0), !dbg !938
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !939
  %12 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !940
  %13 = load i32, i32* %position.addr, align 4, !dbg !941
  call void @literal(%struct.lzma_coder_s* %11, %struct.lzma_mf_s* %12, i32 %13), !dbg !942
  br label %if.end23, !dbg !943

if.else:                                          ; preds = %entry
  %14 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !944
  %rc4 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %14, i32 0, i32 0, !dbg !946
  %15 = load i32, i32* %pos_state, align 4, !dbg !947
  %idxprom5 = zext i32 %15 to i64, !dbg !948
  %16 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !949
  %state6 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %16, i32 0, i32 1, !dbg !950
  %17 = load i32, i32* %state6, align 8, !dbg !950
  %idxprom7 = zext i32 %17 to i64, !dbg !948
  %18 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !948
  %is_match8 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %18, i32 0, i32 13, !dbg !951
  %arrayidx9 = getelementptr inbounds [12 x [16 x i16]], [12 x [16 x i16]]* %is_match8, i64 0, i64 %idxprom7, !dbg !948
  %arrayidx10 = getelementptr inbounds [16 x i16], [16 x i16]* %arrayidx9, i64 0, i64 %idxprom5, !dbg !948
  call void @rc_bit(%struct.lzma_range_encoder* %rc4, i16* %arrayidx10, i32 1), !dbg !952
  %19 = load i32, i32* %back.addr, align 4, !dbg !953
  %cmp11 = icmp ult i32 %19, 4, !dbg !955
  br i1 %cmp11, label %if.then12, label %if.else17, !dbg !956

if.then12:                                        ; preds = %if.else
  %20 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !957
  %rc13 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %20, i32 0, i32 0, !dbg !959
  %21 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !960
  %state14 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %21, i32 0, i32 1, !dbg !961
  %22 = load i32, i32* %state14, align 8, !dbg !961
  %idxprom15 = zext i32 %22 to i64, !dbg !962
  %23 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !962
  %is_rep = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %23, i32 0, i32 14, !dbg !963
  %arrayidx16 = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep, i64 0, i64 %idxprom15, !dbg !962
  call void @rc_bit(%struct.lzma_range_encoder* %rc13, i16* %arrayidx16, i32 1), !dbg !964
  %24 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !965
  %25 = load i32, i32* %pos_state, align 4, !dbg !966
  %26 = load i32, i32* %back.addr, align 4, !dbg !967
  %27 = load i32, i32* %len.addr, align 4, !dbg !968
  call void @rep_match(%struct.lzma_coder_s* %24, i32 %25, i32 %26, i32 %27), !dbg !969
  br label %if.end, !dbg !970

if.else17:                                        ; preds = %if.else
  %28 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !971
  %rc18 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %28, i32 0, i32 0, !dbg !973
  %29 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !974
  %state19 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %29, i32 0, i32 1, !dbg !975
  %30 = load i32, i32* %state19, align 8, !dbg !975
  %idxprom20 = zext i32 %30 to i64, !dbg !976
  %31 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !976
  %is_rep21 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %31, i32 0, i32 14, !dbg !977
  %arrayidx22 = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep21, i64 0, i64 %idxprom20, !dbg !976
  call void @rc_bit(%struct.lzma_range_encoder* %rc18, i16* %arrayidx22, i32 0), !dbg !978
  %32 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !979
  %33 = load i32, i32* %pos_state, align 4, !dbg !980
  %34 = load i32, i32* %back.addr, align 4, !dbg !981
  %sub = sub i32 %34, 4, !dbg !982
  %35 = load i32, i32* %len.addr, align 4, !dbg !983
  call void @match(%struct.lzma_coder_s* %32, i32 %33, i32 %sub, i32 %35), !dbg !984
  br label %if.end

if.end:                                           ; preds = %if.else17, %if.then12
  br label %if.end23

if.end23:                                         ; preds = %if.end, %cond.end
  %36 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !985
  %read_ahead = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %36, i32 0, i32 6, !dbg !985
  %37 = load i32, i32* %read_ahead, align 4, !dbg !985
  %38 = load i32, i32* %len.addr, align 4, !dbg !985
  %cmp24 = icmp uge i32 %37, %38, !dbg !985
  br i1 %cmp24, label %cond.true25, label %cond.false26, !dbg !985

cond.true25:                                      ; preds = %if.end23
  br label %cond.end27, !dbg !986

cond.false26:                                     ; preds = %if.end23
  call void @__assert_fail(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.10, i32 0, i32 0), i8* getelementptr inbounds ([82 x i8], [82 x i8]* @.str.1, i32 0, i32 0), i32 271, i8* getelementptr inbounds ([74 x i8], [74 x i8]* @__PRETTY_FUNCTION__.encode_symbol, i32 0, i32 0)) #6, !dbg !988
  unreachable, !dbg !988
                                                  ; No predecessors!
  br label %cond.end27, !dbg !990

cond.end27:                                       ; preds = %39, %cond.true25
  %40 = load i32, i32* %len.addr, align 4, !dbg !992
  %41 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !993
  %read_ahead28 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %41, i32 0, i32 6, !dbg !994
  %42 = load i32, i32* %read_ahead28, align 4, !dbg !995
  %sub29 = sub i32 %42, %40, !dbg !995
  store i32 %sub29, i32* %read_ahead28, align 4, !dbg !995
  ret void, !dbg !996
}

; Function Attrs: nounwind uwtable
define internal void @encode_eopm(%struct.lzma_coder_s* %coder, i32 %position) #0 !dbg !465 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %position.addr = alloca i32, align 4
  %pos_state = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !997, metadata !514), !dbg !998
  store i32 %position, i32* %position.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %position.addr, metadata !999, metadata !514), !dbg !1000
  call void @llvm.dbg.declare(metadata i32* %pos_state, metadata !1001, metadata !514), !dbg !1002
  %0 = load i32, i32* %position.addr, align 4, !dbg !1003
  %1 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1004
  %pos_mask = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %1, i32 0, i32 9, !dbg !1005
  %2 = load i32, i32* %pos_mask, align 8, !dbg !1005
  %and = and i32 %0, %2, !dbg !1006
  store i32 %and, i32* %pos_state, align 4, !dbg !1002
  %3 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1007
  %rc = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %3, i32 0, i32 0, !dbg !1008
  %4 = load i32, i32* %pos_state, align 4, !dbg !1009
  %idxprom = zext i32 %4 to i64, !dbg !1010
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1011
  %state = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 1, !dbg !1012
  %6 = load i32, i32* %state, align 8, !dbg !1012
  %idxprom1 = zext i32 %6 to i64, !dbg !1010
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1010
  %is_match = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %7, i32 0, i32 13, !dbg !1013
  %arrayidx = getelementptr inbounds [12 x [16 x i16]], [12 x [16 x i16]]* %is_match, i64 0, i64 %idxprom1, !dbg !1010
  %arrayidx2 = getelementptr inbounds [16 x i16], [16 x i16]* %arrayidx, i64 0, i64 %idxprom, !dbg !1010
  call void @rc_bit(%struct.lzma_range_encoder* %rc, i16* %arrayidx2, i32 1), !dbg !1014
  %8 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1015
  %rc3 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %8, i32 0, i32 0, !dbg !1016
  %9 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1017
  %state4 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %9, i32 0, i32 1, !dbg !1018
  %10 = load i32, i32* %state4, align 8, !dbg !1018
  %idxprom5 = zext i32 %10 to i64, !dbg !1019
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1019
  %is_rep = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 14, !dbg !1020
  %arrayidx6 = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep, i64 0, i64 %idxprom5, !dbg !1019
  call void @rc_bit(%struct.lzma_range_encoder* %rc3, i16* %arrayidx6, i32 0), !dbg !1021
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1022
  %13 = load i32, i32* %pos_state, align 4, !dbg !1023
  call void @match(%struct.lzma_coder_s* %12, i32 %13, i32 -1, i32 2), !dbg !1024
  ret void, !dbg !1025
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @rc_flush(%struct.lzma_range_encoder* %rc) #2 !dbg !468 {
entry:
  %rc.addr = alloca %struct.lzma_range_encoder*, align 8
  %i = alloca i64, align 8
  store %struct.lzma_range_encoder* %rc, %struct.lzma_range_encoder** %rc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_range_encoder** %rc.addr, metadata !1026, metadata !514), !dbg !1027
  call void @llvm.dbg.declare(metadata i64* %i, metadata !1028, metadata !514), !dbg !1029
  store i64 0, i64* %i, align 8, !dbg !1030
  br label %for.cond, !dbg !1032

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i64, i64* %i, align 8, !dbg !1033
  %cmp = icmp ult i64 %0, 5, !dbg !1036
  br i1 %cmp, label %for.body, label %for.end, !dbg !1037

for.body:                                         ; preds = %for.cond
  %1 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1038
  %count = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %1, i32 0, i32 4, !dbg !1039
  %2 = load i64, i64* %count, align 8, !dbg !1040
  %inc = add i64 %2, 1, !dbg !1040
  store i64 %inc, i64* %count, align 8, !dbg !1040
  %3 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1041
  %symbols = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %3, i32 0, i32 6, !dbg !1042
  %arrayidx = getelementptr inbounds [58 x i32], [58 x i32]* %symbols, i64 0, i64 %2, !dbg !1041
  store i32 4, i32* %arrayidx, align 4, !dbg !1043
  br label %for.inc, !dbg !1041

for.inc:                                          ; preds = %for.body
  %4 = load i64, i64* %i, align 8, !dbg !1044
  %inc1 = add i64 %4, 1, !dbg !1044
  store i64 %inc1, i64* %i, align 8, !dbg !1044
  br label %for.cond, !dbg !1046

for.end:                                          ; preds = %for.cond
  ret void, !dbg !1047
}

; Function Attrs: nounwind uwtable
define i32 @lzma_lzma_encoder_reset(%struct.lzma_coder_s* %coder, %struct.lzma_options_lzma* %options) #0 !dbg !258 {
entry:
  %retval = alloca i32, align 4
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %options.addr = alloca %struct.lzma_options_lzma*, align 8
  %i = alloca i64, align 8
  %j = alloca i64, align 8
  %bt_i = alloca i32, align 4
  %bt_i52 = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !1048, metadata !514), !dbg !1049
  store %struct.lzma_options_lzma* %options, %struct.lzma_options_lzma** %options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_options_lzma** %options.addr, metadata !1050, metadata !514), !dbg !1051
  call void @llvm.dbg.declare(metadata i64* %i, metadata !1052, metadata !514), !dbg !1053
  call void @llvm.dbg.declare(metadata i64* %j, metadata !1054, metadata !514), !dbg !1055
  %0 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1056
  %call = call zeroext i1 @is_options_valid(%struct.lzma_options_lzma* %0), !dbg !1058
  br i1 %call, label %if.end, label %if.then, !dbg !1059

if.then:                                          ; preds = %entry
  store i32 8, i32* %retval, align 4, !dbg !1060
  br label %return, !dbg !1060

if.end:                                           ; preds = %entry
  %1 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1061
  %pb = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %1, i32 0, i32 5, !dbg !1062
  %2 = load i32, i32* %pb, align 4, !dbg !1062
  %shl = shl i32 1, %2, !dbg !1063
  %sub = sub i32 %shl, 1, !dbg !1064
  %3 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1065
  %pos_mask = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %3, i32 0, i32 9, !dbg !1066
  store i32 %sub, i32* %pos_mask, align 8, !dbg !1067
  %4 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1068
  %lc = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %4, i32 0, i32 3, !dbg !1069
  %5 = load i32, i32* %lc, align 4, !dbg !1069
  %6 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1070
  %literal_context_bits = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %6, i32 0, i32 10, !dbg !1071
  store i32 %5, i32* %literal_context_bits, align 4, !dbg !1072
  %7 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1073
  %lp = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %7, i32 0, i32 4, !dbg !1074
  %8 = load i32, i32* %lp, align 8, !dbg !1074
  %shl1 = shl i32 1, %8, !dbg !1075
  %sub2 = sub i32 %shl1, 1, !dbg !1076
  %9 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1077
  %literal_pos_mask = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %9, i32 0, i32 11, !dbg !1078
  store i32 %sub2, i32* %literal_pos_mask, align 8, !dbg !1079
  %10 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1080
  %rc = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %10, i32 0, i32 0, !dbg !1081
  call void @rc_reset(%struct.lzma_range_encoder* %rc), !dbg !1082
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1083
  %state = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 1, !dbg !1084
  store i32 0, i32* %state, align 8, !dbg !1085
  store i64 0, i64* %i, align 8, !dbg !1086
  br label %for.cond, !dbg !1088

for.cond:                                         ; preds = %for.inc, %if.end
  %12 = load i64, i64* %i, align 8, !dbg !1089
  %cmp = icmp ult i64 %12, 4, !dbg !1092
  br i1 %cmp, label %for.body, label %for.end, !dbg !1093

for.body:                                         ; preds = %for.cond
  %13 = load i64, i64* %i, align 8, !dbg !1094
  %14 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1095
  %reps = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %14, i32 0, i32 2, !dbg !1096
  %arrayidx = getelementptr inbounds [4 x i32], [4 x i32]* %reps, i64 0, i64 %13, !dbg !1095
  store i32 0, i32* %arrayidx, align 4, !dbg !1097
  br label %for.inc, !dbg !1095

for.inc:                                          ; preds = %for.body
  %15 = load i64, i64* %i, align 8, !dbg !1098
  %inc = add i64 %15, 1, !dbg !1098
  store i64 %inc, i64* %i, align 8, !dbg !1098
  br label %for.cond, !dbg !1100

for.end:                                          ; preds = %for.cond
  %16 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1101
  %literal = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %16, i32 0, i32 12, !dbg !1102
  %arraydecay = getelementptr inbounds [16 x [768 x i16]], [16 x [768 x i16]]* %literal, i32 0, i32 0, !dbg !1101
  %17 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1103
  %lc3 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %17, i32 0, i32 3, !dbg !1104
  %18 = load i32, i32* %lc3, align 4, !dbg !1104
  %19 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1105
  %lp4 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %19, i32 0, i32 4, !dbg !1106
  %20 = load i32, i32* %lp4, align 8, !dbg !1106
  call void @literal_init([768 x i16]* %arraydecay, i32 %18, i32 %20), !dbg !1107
  store i64 0, i64* %i, align 8, !dbg !1108
  br label %for.cond5, !dbg !1110

for.cond5:                                        ; preds = %for.inc24, %for.end
  %21 = load i64, i64* %i, align 8, !dbg !1111
  %cmp6 = icmp ult i64 %21, 12, !dbg !1114
  br i1 %cmp6, label %for.body7, label %for.end26, !dbg !1115

for.body7:                                        ; preds = %for.cond5
  store i64 0, i64* %j, align 8, !dbg !1116
  br label %for.cond8, !dbg !1119

for.cond8:                                        ; preds = %for.inc17, %for.body7
  %22 = load i64, i64* %j, align 8, !dbg !1120
  %23 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1123
  %pos_mask9 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %23, i32 0, i32 9, !dbg !1124
  %24 = load i32, i32* %pos_mask9, align 8, !dbg !1124
  %conv = zext i32 %24 to i64, !dbg !1123
  %cmp10 = icmp ule i64 %22, %conv, !dbg !1125
  br i1 %cmp10, label %for.body12, label %for.end19, !dbg !1126

for.body12:                                       ; preds = %for.cond8
  %25 = load i64, i64* %j, align 8, !dbg !1127
  %26 = load i64, i64* %i, align 8, !dbg !1127
  %27 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1127
  %is_match = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %27, i32 0, i32 13, !dbg !1127
  %arrayidx13 = getelementptr inbounds [12 x [16 x i16]], [12 x [16 x i16]]* %is_match, i64 0, i64 %26, !dbg !1127
  %arrayidx14 = getelementptr inbounds [16 x i16], [16 x i16]* %arrayidx13, i64 0, i64 %25, !dbg !1127
  store i16 1024, i16* %arrayidx14, align 2, !dbg !1127
  %28 = load i64, i64* %j, align 8, !dbg !1129
  %29 = load i64, i64* %i, align 8, !dbg !1129
  %30 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1129
  %is_rep0_long = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %30, i32 0, i32 18, !dbg !1129
  %arrayidx15 = getelementptr inbounds [12 x [16 x i16]], [12 x [16 x i16]]* %is_rep0_long, i64 0, i64 %29, !dbg !1129
  %arrayidx16 = getelementptr inbounds [16 x i16], [16 x i16]* %arrayidx15, i64 0, i64 %28, !dbg !1129
  store i16 1024, i16* %arrayidx16, align 2, !dbg !1129
  br label %for.inc17, !dbg !1130

for.inc17:                                        ; preds = %for.body12
  %31 = load i64, i64* %j, align 8, !dbg !1131
  %inc18 = add i64 %31, 1, !dbg !1131
  store i64 %inc18, i64* %j, align 8, !dbg !1131
  br label %for.cond8, !dbg !1133

for.end19:                                        ; preds = %for.cond8
  %32 = load i64, i64* %i, align 8, !dbg !1134
  %33 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1134
  %is_rep = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %33, i32 0, i32 14, !dbg !1134
  %arrayidx20 = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep, i64 0, i64 %32, !dbg !1134
  store i16 1024, i16* %arrayidx20, align 2, !dbg !1134
  %34 = load i64, i64* %i, align 8, !dbg !1135
  %35 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1135
  %is_rep0 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %35, i32 0, i32 15, !dbg !1135
  %arrayidx21 = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep0, i64 0, i64 %34, !dbg !1135
  store i16 1024, i16* %arrayidx21, align 2, !dbg !1135
  %36 = load i64, i64* %i, align 8, !dbg !1136
  %37 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1136
  %is_rep1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %37, i32 0, i32 16, !dbg !1136
  %arrayidx22 = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep1, i64 0, i64 %36, !dbg !1136
  store i16 1024, i16* %arrayidx22, align 2, !dbg !1136
  %38 = load i64, i64* %i, align 8, !dbg !1137
  %39 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1137
  %is_rep2 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %39, i32 0, i32 17, !dbg !1137
  %arrayidx23 = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep2, i64 0, i64 %38, !dbg !1137
  store i16 1024, i16* %arrayidx23, align 2, !dbg !1137
  br label %for.inc24, !dbg !1138

for.inc24:                                        ; preds = %for.end19
  %40 = load i64, i64* %i, align 8, !dbg !1139
  %inc25 = add i64 %40, 1, !dbg !1139
  store i64 %inc25, i64* %i, align 8, !dbg !1139
  br label %for.cond5, !dbg !1141

for.end26:                                        ; preds = %for.cond5
  store i64 0, i64* %i, align 8, !dbg !1142
  br label %for.cond27, !dbg !1144

for.cond27:                                       ; preds = %for.inc32, %for.end26
  %41 = load i64, i64* %i, align 8, !dbg !1145
  %cmp28 = icmp ult i64 %41, 114, !dbg !1148
  br i1 %cmp28, label %for.body30, label %for.end34, !dbg !1149

for.body30:                                       ; preds = %for.cond27
  %42 = load i64, i64* %i, align 8, !dbg !1150
  %43 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1150
  %pos_special = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %43, i32 0, i32 20, !dbg !1150
  %arrayidx31 = getelementptr inbounds [114 x i16], [114 x i16]* %pos_special, i64 0, i64 %42, !dbg !1150
  store i16 1024, i16* %arrayidx31, align 2, !dbg !1150
  br label %for.inc32, !dbg !1150

for.inc32:                                        ; preds = %for.body30
  %44 = load i64, i64* %i, align 8, !dbg !1151
  %inc33 = add i64 %44, 1, !dbg !1151
  store i64 %inc33, i64* %i, align 8, !dbg !1151
  br label %for.cond27, !dbg !1153

for.end34:                                        ; preds = %for.cond27
  store i64 0, i64* %i, align 8, !dbg !1154
  br label %for.cond35, !dbg !1156

for.cond35:                                       ; preds = %for.inc48, %for.end34
  %45 = load i64, i64* %i, align 8, !dbg !1157
  %cmp36 = icmp ult i64 %45, 4, !dbg !1160
  br i1 %cmp36, label %for.body38, label %for.end50, !dbg !1161

for.body38:                                       ; preds = %for.cond35
  br label %do.body, !dbg !1162

do.body:                                          ; preds = %for.body38
  call void @llvm.dbg.declare(metadata i32* %bt_i, metadata !1163, metadata !514), !dbg !1165
  store i32 0, i32* %bt_i, align 4, !dbg !1166
  br label %for.cond39, !dbg !1166

for.cond39:                                       ; preds = %for.inc45, %do.body
  %46 = load i32, i32* %bt_i, align 4, !dbg !1169
  %cmp40 = icmp ult i32 %46, 64, !dbg !1169
  br i1 %cmp40, label %for.body42, label %for.end47, !dbg !1169

for.body42:                                       ; preds = %for.cond39
  %47 = load i32, i32* %bt_i, align 4, !dbg !1172
  %idxprom = zext i32 %47 to i64, !dbg !1172
  %48 = load i64, i64* %i, align 8, !dbg !1172
  %49 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1172
  %pos_slot = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %49, i32 0, i32 19, !dbg !1172
  %arrayidx43 = getelementptr inbounds [4 x [64 x i16]], [4 x [64 x i16]]* %pos_slot, i64 0, i64 %48, !dbg !1172
  %arrayidx44 = getelementptr inbounds [64 x i16], [64 x i16]* %arrayidx43, i64 0, i64 %idxprom, !dbg !1172
  store i16 1024, i16* %arrayidx44, align 2, !dbg !1172
  br label %for.inc45, !dbg !1172

for.inc45:                                        ; preds = %for.body42
  %50 = load i32, i32* %bt_i, align 4, !dbg !1174
  %inc46 = add i32 %50, 1, !dbg !1174
  store i32 %inc46, i32* %bt_i, align 4, !dbg !1174
  br label %for.cond39, !dbg !1174

for.end47:                                        ; preds = %for.cond39
  br label %do.end, !dbg !1176

do.end:                                           ; preds = %for.end47
  br label %for.inc48, !dbg !1178

for.inc48:                                        ; preds = %do.end
  %51 = load i64, i64* %i, align 8, !dbg !1180
  %inc49 = add i64 %51, 1, !dbg !1180
  store i64 %inc49, i64* %i, align 8, !dbg !1180
  br label %for.cond35, !dbg !1182

for.end50:                                        ; preds = %for.cond35
  br label %do.body51, !dbg !1183

do.body51:                                        ; preds = %for.end50
  call void @llvm.dbg.declare(metadata i32* %bt_i52, metadata !1184, metadata !514), !dbg !1186
  store i32 0, i32* %bt_i52, align 4, !dbg !1187
  br label %for.cond53, !dbg !1187

for.cond53:                                       ; preds = %for.inc59, %do.body51
  %52 = load i32, i32* %bt_i52, align 4, !dbg !1190
  %cmp54 = icmp ult i32 %52, 16, !dbg !1190
  br i1 %cmp54, label %for.body56, label %for.end61, !dbg !1190

for.body56:                                       ; preds = %for.cond53
  %53 = load i32, i32* %bt_i52, align 4, !dbg !1193
  %idxprom57 = zext i32 %53 to i64, !dbg !1193
  %54 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1193
  %pos_align = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %54, i32 0, i32 21, !dbg !1193
  %arrayidx58 = getelementptr inbounds [16 x i16], [16 x i16]* %pos_align, i64 0, i64 %idxprom57, !dbg !1193
  store i16 1024, i16* %arrayidx58, align 2, !dbg !1193
  br label %for.inc59, !dbg !1193

for.inc59:                                        ; preds = %for.body56
  %55 = load i32, i32* %bt_i52, align 4, !dbg !1195
  %inc60 = add i32 %55, 1, !dbg !1195
  store i32 %inc60, i32* %bt_i52, align 4, !dbg !1195
  br label %for.cond53, !dbg !1195

for.end61:                                        ; preds = %for.cond53
  br label %do.end62, !dbg !1197

do.end62:                                         ; preds = %for.end61
  %56 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1199
  %match_len_encoder = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %56, i32 0, i32 22, !dbg !1200
  %57 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1201
  %pb63 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %57, i32 0, i32 5, !dbg !1202
  %58 = load i32, i32* %pb63, align 4, !dbg !1202
  %shl64 = shl i32 1, %58, !dbg !1203
  %59 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1204
  %fast_mode = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %59, i32 0, i32 6, !dbg !1205
  %60 = load i8, i8* %fast_mode, align 4, !dbg !1205
  %tobool = trunc i8 %60 to i1, !dbg !1205
  call void @length_encoder_reset(%struct.lzma_length_encoder* %match_len_encoder, i32 %shl64, i1 zeroext %tobool), !dbg !1206
  %61 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1207
  %rep_len_encoder = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %61, i32 0, i32 23, !dbg !1208
  %62 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1209
  %pb65 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %62, i32 0, i32 5, !dbg !1210
  %63 = load i32, i32* %pb65, align 4, !dbg !1210
  %shl66 = shl i32 1, %63, !dbg !1211
  %64 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1212
  %fast_mode67 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %64, i32 0, i32 6, !dbg !1213
  %65 = load i8, i8* %fast_mode67, align 4, !dbg !1213
  %tobool68 = trunc i8 %65 to i1, !dbg !1213
  call void @length_encoder_reset(%struct.lzma_length_encoder* %rep_len_encoder, i32 %shl66, i1 zeroext %tobool68), !dbg !1214
  %66 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1215
  %match_price_count = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %66, i32 0, i32 27, !dbg !1216
  store i32 2147483647, i32* %match_price_count, align 4, !dbg !1217
  %67 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1218
  %align_price_count = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %67, i32 0, i32 29, !dbg !1219
  store i32 2147483647, i32* %align_price_count, align 8, !dbg !1220
  %68 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1221
  %opts_end_index = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %68, i32 0, i32 30, !dbg !1222
  store i32 0, i32* %opts_end_index, align 4, !dbg !1223
  %69 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1224
  %opts_current_index = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %69, i32 0, i32 31, !dbg !1225
  store i32 0, i32* %opts_current_index, align 8, !dbg !1226
  store i32 0, i32* %retval, align 4, !dbg !1227
  br label %return, !dbg !1227

return:                                           ; preds = %do.end62, %if.then
  %70 = load i32, i32* %retval, align 4, !dbg !1228
  ret i32 %70, !dbg !1228
}

; Function Attrs: nounwind uwtable
define internal zeroext i1 @is_options_valid(%struct.lzma_options_lzma* %options) #0 !dbg !471 {
entry:
  %options.addr = alloca %struct.lzma_options_lzma*, align 8
  store %struct.lzma_options_lzma* %options, %struct.lzma_options_lzma** %options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_options_lzma** %options.addr, metadata !1229, metadata !514), !dbg !1230
  %0 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1231
  %call = call zeroext i1 @is_lclppb_valid(%struct.lzma_options_lzma* %0), !dbg !1232
  br i1 %call, label %land.lhs.true, label %land.end, !dbg !1233

land.lhs.true:                                    ; preds = %entry
  %1 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1234
  %nice_len = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %1, i32 0, i32 7, !dbg !1236
  %2 = load i32, i32* %nice_len, align 4, !dbg !1236
  %cmp = icmp uge i32 %2, 2, !dbg !1237
  br i1 %cmp, label %land.lhs.true1, label %land.end, !dbg !1238

land.lhs.true1:                                   ; preds = %land.lhs.true
  %3 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1239
  %nice_len2 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %3, i32 0, i32 7, !dbg !1240
  %4 = load i32, i32* %nice_len2, align 4, !dbg !1240
  %cmp3 = icmp ule i32 %4, 273, !dbg !1241
  br i1 %cmp3, label %land.rhs, label %land.end, !dbg !1242

land.rhs:                                         ; preds = %land.lhs.true1
  %5 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1243
  %mode = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %5, i32 0, i32 6, !dbg !1244
  %6 = load i32, i32* %mode, align 8, !dbg !1244
  %cmp4 = icmp eq i32 %6, 1, !dbg !1245
  br i1 %cmp4, label %lor.end, label %lor.rhs, !dbg !1246

lor.rhs:                                          ; preds = %land.rhs
  %7 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1247
  %mode5 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %7, i32 0, i32 6, !dbg !1248
  %8 = load i32, i32* %mode5, align 8, !dbg !1248
  %cmp6 = icmp eq i32 %8, 2, !dbg !1249
  br label %lor.end, !dbg !1250

lor.end:                                          ; preds = %lor.rhs, %land.rhs
  %9 = phi i1 [ true, %land.rhs ], [ %cmp6, %lor.rhs ]
  br label %land.end

land.end:                                         ; preds = %lor.end, %land.lhs.true1, %land.lhs.true, %entry
  %10 = phi i1 [ false, %land.lhs.true1 ], [ false, %land.lhs.true ], [ false, %entry ], [ %9, %lor.end ]
  ret i1 %10, !dbg !1251
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @rc_reset(%struct.lzma_range_encoder* %rc) #2 !dbg !474 {
entry:
  %rc.addr = alloca %struct.lzma_range_encoder*, align 8
  store %struct.lzma_range_encoder* %rc, %struct.lzma_range_encoder** %rc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_range_encoder** %rc.addr, metadata !1252, metadata !514), !dbg !1253
  %0 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1254
  %low = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %0, i32 0, i32 0, !dbg !1255
  store i64 0, i64* %low, align 8, !dbg !1256
  %1 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1257
  %cache_size = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %1, i32 0, i32 1, !dbg !1258
  store i64 1, i64* %cache_size, align 8, !dbg !1259
  %2 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1260
  %range = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %2, i32 0, i32 2, !dbg !1261
  store i32 -1, i32* %range, align 8, !dbg !1262
  %3 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1263
  %cache = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %3, i32 0, i32 3, !dbg !1264
  store i8 0, i8* %cache, align 4, !dbg !1265
  %4 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1266
  %count = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %4, i32 0, i32 4, !dbg !1267
  store i64 0, i64* %count, align 8, !dbg !1268
  %5 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1269
  %pos = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %5, i32 0, i32 5, !dbg !1270
  store i64 0, i64* %pos, align 8, !dbg !1271
  ret void, !dbg !1272
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @literal_init([768 x i16]* %probs, i32 %lc, i32 %lp) #2 !dbg !475 {
entry:
  %probs.addr = alloca [768 x i16]*, align 8
  %lc.addr = alloca i32, align 4
  %lp.addr = alloca i32, align 4
  %coders = alloca i32, align 4
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  store [768 x i16]* %probs, [768 x i16]** %probs.addr, align 8
  call void @llvm.dbg.declare(metadata [768 x i16]** %probs.addr, metadata !1273, metadata !514), !dbg !1274
  store i32 %lc, i32* %lc.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %lc.addr, metadata !1275, metadata !514), !dbg !1276
  store i32 %lp, i32* %lp.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %lp.addr, metadata !1277, metadata !514), !dbg !1278
  call void @llvm.dbg.declare(metadata i32* %coders, metadata !1279, metadata !514), !dbg !1280
  call void @llvm.dbg.declare(metadata i32* %i, metadata !1281, metadata !514), !dbg !1282
  call void @llvm.dbg.declare(metadata i32* %j, metadata !1283, metadata !514), !dbg !1284
  %0 = load i32, i32* %lc.addr, align 4, !dbg !1285
  %1 = load i32, i32* %lp.addr, align 4, !dbg !1285
  %add = add i32 %0, %1, !dbg !1285
  %cmp = icmp ule i32 %add, 4, !dbg !1285
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1285

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !1286

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.12, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @.str.13, i32 0, i32 0), i32 135, i8* getelementptr inbounds ([60 x i8], [60 x i8]* @__PRETTY_FUNCTION__.literal_init, i32 0, i32 0)) #6, !dbg !1288
  unreachable, !dbg !1288
                                                  ; No predecessors!
  br label %cond.end, !dbg !1290

cond.end:                                         ; preds = %2, %cond.true
  %3 = load i32, i32* %lc.addr, align 4, !dbg !1292
  %4 = load i32, i32* %lp.addr, align 4, !dbg !1293
  %add1 = add i32 %3, %4, !dbg !1294
  %shl = shl i32 1, %add1, !dbg !1295
  store i32 %shl, i32* %coders, align 4, !dbg !1296
  store i32 0, i32* %i, align 4, !dbg !1297
  br label %for.cond, !dbg !1299

for.cond:                                         ; preds = %for.inc8, %cond.end
  %5 = load i32, i32* %i, align 4, !dbg !1300
  %6 = load i32, i32* %coders, align 4, !dbg !1303
  %cmp2 = icmp ult i32 %5, %6, !dbg !1304
  br i1 %cmp2, label %for.body, label %for.end10, !dbg !1305

for.body:                                         ; preds = %for.cond
  store i32 0, i32* %j, align 4, !dbg !1306
  br label %for.cond3, !dbg !1308

for.cond3:                                        ; preds = %for.inc, %for.body
  %7 = load i32, i32* %j, align 4, !dbg !1309
  %cmp4 = icmp ult i32 %7, 768, !dbg !1312
  br i1 %cmp4, label %for.body5, label %for.end, !dbg !1313

for.body5:                                        ; preds = %for.cond3
  %8 = load i32, i32* %j, align 4, !dbg !1314
  %idxprom = zext i32 %8 to i64, !dbg !1314
  %9 = load i32, i32* %i, align 4, !dbg !1314
  %idxprom6 = zext i32 %9 to i64, !dbg !1314
  %10 = load [768 x i16]*, [768 x i16]** %probs.addr, align 8, !dbg !1314
  %arrayidx = getelementptr inbounds [768 x i16], [768 x i16]* %10, i64 %idxprom6, !dbg !1314
  %arrayidx7 = getelementptr inbounds [768 x i16], [768 x i16]* %arrayidx, i64 0, i64 %idxprom, !dbg !1314
  store i16 1024, i16* %arrayidx7, align 2, !dbg !1314
  br label %for.inc, !dbg !1314

for.inc:                                          ; preds = %for.body5
  %11 = load i32, i32* %j, align 4, !dbg !1315
  %inc = add i32 %11, 1, !dbg !1315
  store i32 %inc, i32* %j, align 4, !dbg !1315
  br label %for.cond3, !dbg !1317

for.end:                                          ; preds = %for.cond3
  br label %for.inc8, !dbg !1318

for.inc8:                                         ; preds = %for.end
  %12 = load i32, i32* %i, align 4, !dbg !1320
  %inc9 = add i32 %12, 1, !dbg !1320
  store i32 %inc9, i32* %i, align 4, !dbg !1320
  br label %for.cond, !dbg !1322

for.end10:                                        ; preds = %for.cond
  ret void, !dbg !1323
}

; Function Attrs: nounwind uwtable
define internal void @length_encoder_reset(%struct.lzma_length_encoder* %lencoder, i32 %num_pos_states, i1 zeroext %fast_mode) #0 !dbg !481 {
entry:
  %lencoder.addr = alloca %struct.lzma_length_encoder*, align 8
  %num_pos_states.addr = alloca i32, align 4
  %fast_mode.addr = alloca i8, align 1
  %pos_state = alloca i64, align 8
  %bt_i = alloca i32, align 4
  %bt_i8 = alloca i32, align 4
  %bt_i24 = alloca i32, align 4
  store %struct.lzma_length_encoder* %lencoder, %struct.lzma_length_encoder** %lencoder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_length_encoder** %lencoder.addr, metadata !1324, metadata !514), !dbg !1325
  store i32 %num_pos_states, i32* %num_pos_states.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %num_pos_states.addr, metadata !1326, metadata !514), !dbg !1327
  %frombool = zext i1 %fast_mode to i8
  store i8 %frombool, i8* %fast_mode.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %fast_mode.addr, metadata !1328, metadata !514), !dbg !1329
  call void @llvm.dbg.declare(metadata i64* %pos_state, metadata !1330, metadata !514), !dbg !1331
  %0 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lencoder.addr, align 8, !dbg !1332
  %choice = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %0, i32 0, i32 0, !dbg !1332
  store i16 1024, i16* %choice, align 4, !dbg !1332
  %1 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lencoder.addr, align 8, !dbg !1333
  %choice2 = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %1, i32 0, i32 1, !dbg !1333
  store i16 1024, i16* %choice2, align 2, !dbg !1333
  store i64 0, i64* %pos_state, align 8, !dbg !1334
  br label %for.cond, !dbg !1336

for.cond:                                         ; preds = %for.inc20, %entry
  %2 = load i64, i64* %pos_state, align 8, !dbg !1337
  %3 = load i32, i32* %num_pos_states.addr, align 4, !dbg !1340
  %conv = zext i32 %3 to i64, !dbg !1340
  %cmp = icmp ult i64 %2, %conv, !dbg !1341
  br i1 %cmp, label %for.body, label %for.end22, !dbg !1342

for.body:                                         ; preds = %for.cond
  br label %do.body, !dbg !1343

do.body:                                          ; preds = %for.body
  call void @llvm.dbg.declare(metadata i32* %bt_i, metadata !1345, metadata !514), !dbg !1347
  store i32 0, i32* %bt_i, align 4, !dbg !1348
  br label %for.cond2, !dbg !1348

for.cond2:                                        ; preds = %for.inc, %do.body
  %4 = load i32, i32* %bt_i, align 4, !dbg !1351
  %cmp3 = icmp ult i32 %4, 8, !dbg !1351
  br i1 %cmp3, label %for.body5, label %for.end, !dbg !1351

for.body5:                                        ; preds = %for.cond2
  %5 = load i32, i32* %bt_i, align 4, !dbg !1354
  %idxprom = zext i32 %5 to i64, !dbg !1354
  %6 = load i64, i64* %pos_state, align 8, !dbg !1354
  %7 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lencoder.addr, align 8, !dbg !1354
  %low = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %7, i32 0, i32 2, !dbg !1354
  %arrayidx = getelementptr inbounds [16 x [8 x i16]], [16 x [8 x i16]]* %low, i64 0, i64 %6, !dbg !1354
  %arrayidx6 = getelementptr inbounds [8 x i16], [8 x i16]* %arrayidx, i64 0, i64 %idxprom, !dbg !1354
  store i16 1024, i16* %arrayidx6, align 2, !dbg !1354
  br label %for.inc, !dbg !1354

for.inc:                                          ; preds = %for.body5
  %8 = load i32, i32* %bt_i, align 4, !dbg !1356
  %inc = add i32 %8, 1, !dbg !1356
  store i32 %inc, i32* %bt_i, align 4, !dbg !1356
  br label %for.cond2, !dbg !1356

for.end:                                          ; preds = %for.cond2
  br label %do.end, !dbg !1358

do.end:                                           ; preds = %for.end
  br label %do.body7, !dbg !1360

do.body7:                                         ; preds = %do.end
  call void @llvm.dbg.declare(metadata i32* %bt_i8, metadata !1361, metadata !514), !dbg !1363
  store i32 0, i32* %bt_i8, align 4, !dbg !1364
  br label %for.cond9, !dbg !1364

for.cond9:                                        ; preds = %for.inc16, %do.body7
  %9 = load i32, i32* %bt_i8, align 4, !dbg !1367
  %cmp10 = icmp ult i32 %9, 8, !dbg !1367
  br i1 %cmp10, label %for.body12, label %for.end18, !dbg !1367

for.body12:                                       ; preds = %for.cond9
  %10 = load i32, i32* %bt_i8, align 4, !dbg !1370
  %idxprom13 = zext i32 %10 to i64, !dbg !1370
  %11 = load i64, i64* %pos_state, align 8, !dbg !1370
  %12 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lencoder.addr, align 8, !dbg !1370
  %mid = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %12, i32 0, i32 3, !dbg !1370
  %arrayidx14 = getelementptr inbounds [16 x [8 x i16]], [16 x [8 x i16]]* %mid, i64 0, i64 %11, !dbg !1370
  %arrayidx15 = getelementptr inbounds [8 x i16], [8 x i16]* %arrayidx14, i64 0, i64 %idxprom13, !dbg !1370
  store i16 1024, i16* %arrayidx15, align 2, !dbg !1370
  br label %for.inc16, !dbg !1370

for.inc16:                                        ; preds = %for.body12
  %13 = load i32, i32* %bt_i8, align 4, !dbg !1372
  %inc17 = add i32 %13, 1, !dbg !1372
  store i32 %inc17, i32* %bt_i8, align 4, !dbg !1372
  br label %for.cond9, !dbg !1372

for.end18:                                        ; preds = %for.cond9
  br label %do.end19, !dbg !1374

do.end19:                                         ; preds = %for.end18
  br label %for.inc20, !dbg !1376

for.inc20:                                        ; preds = %do.end19
  %14 = load i64, i64* %pos_state, align 8, !dbg !1377
  %inc21 = add i64 %14, 1, !dbg !1377
  store i64 %inc21, i64* %pos_state, align 8, !dbg !1377
  br label %for.cond, !dbg !1379

for.end22:                                        ; preds = %for.cond
  br label %do.body23, !dbg !1380

do.body23:                                        ; preds = %for.end22
  call void @llvm.dbg.declare(metadata i32* %bt_i24, metadata !1381, metadata !514), !dbg !1383
  store i32 0, i32* %bt_i24, align 4, !dbg !1384
  br label %for.cond25, !dbg !1384

for.cond25:                                       ; preds = %for.inc31, %do.body23
  %15 = load i32, i32* %bt_i24, align 4, !dbg !1387
  %cmp26 = icmp ult i32 %15, 256, !dbg !1387
  br i1 %cmp26, label %for.body28, label %for.end33, !dbg !1387

for.body28:                                       ; preds = %for.cond25
  %16 = load i32, i32* %bt_i24, align 4, !dbg !1390
  %idxprom29 = zext i32 %16 to i64, !dbg !1390
  %17 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lencoder.addr, align 8, !dbg !1390
  %high = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %17, i32 0, i32 4, !dbg !1390
  %arrayidx30 = getelementptr inbounds [256 x i16], [256 x i16]* %high, i64 0, i64 %idxprom29, !dbg !1390
  store i16 1024, i16* %arrayidx30, align 2, !dbg !1390
  br label %for.inc31, !dbg !1390

for.inc31:                                        ; preds = %for.body28
  %18 = load i32, i32* %bt_i24, align 4, !dbg !1392
  %inc32 = add i32 %18, 1, !dbg !1392
  store i32 %inc32, i32* %bt_i24, align 4, !dbg !1392
  br label %for.cond25, !dbg !1392

for.end33:                                        ; preds = %for.cond25
  br label %do.end34, !dbg !1394

do.end34:                                         ; preds = %for.end33
  %19 = load i8, i8* %fast_mode.addr, align 1, !dbg !1396
  %tobool = trunc i8 %19 to i1, !dbg !1396
  br i1 %tobool, label %if.end, label %if.then, !dbg !1398

if.then:                                          ; preds = %do.end34
  store i64 0, i64* %pos_state, align 8, !dbg !1399
  br label %for.cond35, !dbg !1401

for.cond35:                                       ; preds = %for.inc41, %if.then
  %20 = load i64, i64* %pos_state, align 8, !dbg !1402
  %21 = load i32, i32* %num_pos_states.addr, align 4, !dbg !1405
  %conv36 = zext i32 %21 to i64, !dbg !1405
  %cmp37 = icmp ult i64 %20, %conv36, !dbg !1406
  br i1 %cmp37, label %for.body39, label %for.end43, !dbg !1407

for.body39:                                       ; preds = %for.cond35
  %22 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lencoder.addr, align 8, !dbg !1408
  %23 = load i64, i64* %pos_state, align 8, !dbg !1409
  %conv40 = trunc i64 %23 to i32, !dbg !1409
  call void @length_update_prices(%struct.lzma_length_encoder* %22, i32 %conv40), !dbg !1410
  br label %for.inc41, !dbg !1410

for.inc41:                                        ; preds = %for.body39
  %24 = load i64, i64* %pos_state, align 8, !dbg !1411
  %inc42 = add i64 %24, 1, !dbg !1411
  store i64 %inc42, i64* %pos_state, align 8, !dbg !1411
  br label %for.cond35, !dbg !1412

for.end43:                                        ; preds = %for.cond35
  br label %if.end, !dbg !1414

if.end:                                           ; preds = %for.end43, %do.end34
  ret void, !dbg !1416
}

; Function Attrs: nounwind uwtable
define i32 @lzma_lzma_encoder_create(%struct.lzma_coder_s** %coder_ptr, %struct.lzma_allocator* %allocator, %struct.lzma_options_lzma* %options, %struct.lzma_lz_options* %lz_options) #0 !dbg !295 {
entry:
  %retval = alloca i32, align 4
  %coder_ptr.addr = alloca %struct.lzma_coder_s**, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %options.addr = alloca %struct.lzma_options_lzma*, align 8
  %lz_options.addr = alloca %struct.lzma_lz_options*, align 8
  %coder = alloca %struct.lzma_coder_s*, align 8
  %log_size = alloca i32, align 4
  store %struct.lzma_coder_s** %coder_ptr, %struct.lzma_coder_s*** %coder_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s*** %coder_ptr.addr, metadata !1417, metadata !514), !dbg !1418
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !1419, metadata !514), !dbg !1420
  store %struct.lzma_options_lzma* %options, %struct.lzma_options_lzma** %options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_options_lzma** %options.addr, metadata !1421, metadata !514), !dbg !1422
  store %struct.lzma_lz_options* %lz_options, %struct.lzma_lz_options** %lz_options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_lz_options** %lz_options.addr, metadata !1423, metadata !514), !dbg !1424
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder, metadata !1425, metadata !514), !dbg !1426
  call void @llvm.dbg.declare(metadata i32* %log_size, metadata !1427, metadata !514), !dbg !1428
  store i32 0, i32* %log_size, align 4, !dbg !1428
  %0 = load %struct.lzma_coder_s**, %struct.lzma_coder_s*** %coder_ptr.addr, align 8, !dbg !1429
  %1 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %0, align 8, !dbg !1431
  %cmp = icmp eq %struct.lzma_coder_s* %1, null, !dbg !1432
  br i1 %cmp, label %if.then, label %if.end3, !dbg !1433

if.then:                                          ; preds = %entry
  %2 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !1434
  %call = call noalias i8* @lzma_alloc(i64 249576, %struct.lzma_allocator* %2), !dbg !1436
  %3 = bitcast i8* %call to %struct.lzma_coder_s*, !dbg !1436
  %4 = load %struct.lzma_coder_s**, %struct.lzma_coder_s*** %coder_ptr.addr, align 8, !dbg !1437
  store %struct.lzma_coder_s* %3, %struct.lzma_coder_s** %4, align 8, !dbg !1438
  %5 = load %struct.lzma_coder_s**, %struct.lzma_coder_s*** %coder_ptr.addr, align 8, !dbg !1439
  %6 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %5, align 8, !dbg !1441
  %cmp1 = icmp eq %struct.lzma_coder_s* %6, null, !dbg !1442
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !1443

if.then2:                                         ; preds = %if.then
  store i32 5, i32* %retval, align 4, !dbg !1444
  br label %return, !dbg !1444

if.end:                                           ; preds = %if.then
  br label %if.end3, !dbg !1445

if.end3:                                          ; preds = %if.end, %entry
  %7 = load %struct.lzma_coder_s**, %struct.lzma_coder_s*** %coder_ptr.addr, align 8, !dbg !1446
  %8 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %7, align 8, !dbg !1447
  store %struct.lzma_coder_s* %8, %struct.lzma_coder_s** %coder, align 8, !dbg !1448
  %9 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1449
  %mode = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %9, i32 0, i32 6, !dbg !1450
  %10 = load i32, i32* %mode, align 8, !dbg !1450
  switch i32 %10, label %sw.default [
    i32 1, label %sw.bb
    i32 2, label %sw.bb4
  ], !dbg !1451

sw.bb:                                            ; preds = %if.end3
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !1452
  %fast_mode = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 6, !dbg !1454
  store i8 1, i8* %fast_mode, align 4, !dbg !1455
  br label %sw.epilog, !dbg !1456

sw.bb4:                                           ; preds = %if.end3
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !1457
  %fast_mode5 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %12, i32 0, i32 6, !dbg !1459
  store i8 0, i8* %fast_mode5, align 4, !dbg !1460
  br label %while.cond, !dbg !1461

while.cond:                                       ; preds = %while.body, %sw.bb4
  %13 = load i32, i32* %log_size, align 4, !dbg !1462
  %shl = shl i32 1, %13, !dbg !1464
  %14 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1465
  %dict_size = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %14, i32 0, i32 0, !dbg !1466
  %15 = load i32, i32* %dict_size, align 8, !dbg !1466
  %cmp6 = icmp ult i32 %shl, %15, !dbg !1467
  br i1 %cmp6, label %while.body, label %while.end, !dbg !1468

while.body:                                       ; preds = %while.cond
  %16 = load i32, i32* %log_size, align 4, !dbg !1469
  %inc = add i32 %16, 1, !dbg !1469
  store i32 %inc, i32* %log_size, align 4, !dbg !1469
  br label %while.cond, !dbg !1470

while.end:                                        ; preds = %while.cond
  %17 = load i32, i32* %log_size, align 4, !dbg !1472
  %mul = mul i32 %17, 2, !dbg !1473
  %18 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !1474
  %dist_table_size = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %18, i32 0, i32 26, !dbg !1475
  store i32 %mul, i32* %dist_table_size, align 8, !dbg !1476
  %19 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1477
  %nice_len = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %19, i32 0, i32 7, !dbg !1478
  %20 = load i32, i32* %nice_len, align 4, !dbg !1478
  %add = add i32 %20, 1, !dbg !1479
  %sub = sub i32 %add, 2, !dbg !1480
  %21 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !1481
  %match_len_encoder = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %21, i32 0, i32 22, !dbg !1482
  %table_size = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %match_len_encoder, i32 0, i32 6, !dbg !1483
  store i32 %sub, i32* %table_size, align 4, !dbg !1484
  %22 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1485
  %nice_len7 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %22, i32 0, i32 7, !dbg !1486
  %23 = load i32, i32* %nice_len7, align 4, !dbg !1486
  %add8 = add i32 %23, 1, !dbg !1487
  %sub9 = sub i32 %add8, 2, !dbg !1488
  %24 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !1489
  %rep_len_encoder = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %24, i32 0, i32 23, !dbg !1490
  %table_size10 = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %rep_len_encoder, i32 0, i32 6, !dbg !1491
  store i32 %sub9, i32* %table_size10, align 4, !dbg !1492
  br label %sw.epilog, !dbg !1493

sw.default:                                       ; preds = %if.end3
  store i32 8, i32* %retval, align 4, !dbg !1494
  br label %return, !dbg !1494

sw.epilog:                                        ; preds = %while.end, %sw.bb
  %25 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1495
  %preset_dict = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %25, i32 0, i32 1, !dbg !1496
  %26 = load i8*, i8** %preset_dict, align 8, !dbg !1496
  %cmp11 = icmp ne i8* %26, null, !dbg !1497
  br i1 %cmp11, label %land.rhs, label %land.end, !dbg !1498

land.rhs:                                         ; preds = %sw.epilog
  %27 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1499
  %preset_dict_size = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %27, i32 0, i32 2, !dbg !1501
  %28 = load i32, i32* %preset_dict_size, align 8, !dbg !1501
  %cmp12 = icmp ugt i32 %28, 0, !dbg !1502
  br label %land.end

land.end:                                         ; preds = %land.rhs, %sw.epilog
  %29 = phi i1 [ false, %sw.epilog ], [ %cmp12, %land.rhs ]
  %30 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !1503
  %is_initialized = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %30, i32 0, i32 7, !dbg !1504
  %frombool = zext i1 %29 to i8, !dbg !1505
  store i8 %frombool, i8* %is_initialized, align 1, !dbg !1505
  %31 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !1506
  %is_flushed = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %31, i32 0, i32 8, !dbg !1507
  store i8 0, i8* %is_flushed, align 2, !dbg !1508
  %32 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !1509
  %33 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1510
  call void @set_lz_options(%struct.lzma_lz_options* %32, %struct.lzma_options_lzma* %33), !dbg !1511
  %34 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !1512
  %35 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1513
  %call13 = call i32 @lzma_lzma_encoder_reset(%struct.lzma_coder_s* %34, %struct.lzma_options_lzma* %35), !dbg !1514
  store i32 %call13, i32* %retval, align 4, !dbg !1515
  br label %return, !dbg !1515

return:                                           ; preds = %land.end, %sw.default, %if.then2
  %36 = load i32, i32* %retval, align 4, !dbg !1516
  ret i32 %36, !dbg !1516
}

declare noalias i8* @lzma_alloc(i64, %struct.lzma_allocator*) #4

; Function Attrs: nounwind uwtable
define internal void @set_lz_options(%struct.lzma_lz_options* %lz_options, %struct.lzma_options_lzma* %options) #0 !dbg !484 {
entry:
  %lz_options.addr = alloca %struct.lzma_lz_options*, align 8
  %options.addr = alloca %struct.lzma_options_lzma*, align 8
  store %struct.lzma_lz_options* %lz_options, %struct.lzma_lz_options** %lz_options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_lz_options** %lz_options.addr, metadata !1517, metadata !514), !dbg !1518
  store %struct.lzma_options_lzma* %options, %struct.lzma_options_lzma** %options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_options_lzma** %options.addr, metadata !1519, metadata !514), !dbg !1520
  %0 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !1521
  %before_size = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %0, i32 0, i32 0, !dbg !1522
  store i64 4096, i64* %before_size, align 8, !dbg !1523
  %1 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1524
  %dict_size = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %1, i32 0, i32 0, !dbg !1525
  %2 = load i32, i32* %dict_size, align 8, !dbg !1525
  %conv = zext i32 %2 to i64, !dbg !1524
  %3 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !1526
  %dict_size1 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %3, i32 0, i32 1, !dbg !1527
  store i64 %conv, i64* %dict_size1, align 8, !dbg !1528
  %4 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !1529
  %after_size = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %4, i32 0, i32 2, !dbg !1530
  store i64 4097, i64* %after_size, align 8, !dbg !1531
  %5 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !1532
  %match_len_max = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %5, i32 0, i32 3, !dbg !1533
  store i64 273, i64* %match_len_max, align 8, !dbg !1534
  %6 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1535
  %nice_len = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %6, i32 0, i32 7, !dbg !1536
  %7 = load i32, i32* %nice_len, align 4, !dbg !1536
  %conv2 = zext i32 %7 to i64, !dbg !1535
  %8 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !1537
  %nice_len3 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %8, i32 0, i32 4, !dbg !1538
  store i64 %conv2, i64* %nice_len3, align 8, !dbg !1539
  %9 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1540
  %mf = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %9, i32 0, i32 8, !dbg !1541
  %10 = load i32, i32* %mf, align 8, !dbg !1541
  %11 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !1542
  %match_finder = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %11, i32 0, i32 5, !dbg !1543
  store i32 %10, i32* %match_finder, align 8, !dbg !1544
  %12 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1545
  %depth = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %12, i32 0, i32 9, !dbg !1546
  %13 = load i32, i32* %depth, align 4, !dbg !1546
  %14 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !1547
  %depth4 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %14, i32 0, i32 6, !dbg !1548
  store i32 %13, i32* %depth4, align 4, !dbg !1549
  %15 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1550
  %preset_dict = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %15, i32 0, i32 1, !dbg !1551
  %16 = load i8*, i8** %preset_dict, align 8, !dbg !1551
  %17 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !1552
  %preset_dict5 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %17, i32 0, i32 7, !dbg !1553
  store i8* %16, i8** %preset_dict5, align 8, !dbg !1554
  %18 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1555
  %preset_dict_size = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %18, i32 0, i32 2, !dbg !1556
  %19 = load i32, i32* %preset_dict_size, align 8, !dbg !1556
  %20 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !1557
  %preset_dict_size6 = getelementptr inbounds %struct.lzma_lz_options, %struct.lzma_lz_options* %20, i32 0, i32 8, !dbg !1558
  store i32 %19, i32* %preset_dict_size6, align 8, !dbg !1559
  ret void, !dbg !1560
}

; Function Attrs: nounwind uwtable
define i32 @lzma_lzma_encoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_filter_info_s* %filters) #0 !dbg !325 {
entry:
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %filters.addr = alloca %struct.lzma_filter_info_s*, align 8
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !1561, metadata !514), !dbg !1562
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !1563, metadata !514), !dbg !1564
  store %struct.lzma_filter_info_s* %filters, %struct.lzma_filter_info_s** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter_info_s** %filters.addr, metadata !1565, metadata !514), !dbg !1566
  %0 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !1567
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !1568
  %2 = load %struct.lzma_filter_info_s*, %struct.lzma_filter_info_s** %filters.addr, align 8, !dbg !1569
  %call = call i32 @lzma_lz_encoder_init(%struct.lzma_next_coder_s* %0, %struct.lzma_allocator* %1, %struct.lzma_filter_info_s* %2, i32 (%struct.lzma_lz_encoder*, %struct.lzma_allocator*, i8*, %struct.lzma_lz_options*)* @lzma_encoder_init), !dbg !1570
  ret i32 %call, !dbg !1571
}

declare i32 @lzma_lz_encoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter_info_s*, i32 (%struct.lzma_lz_encoder*, %struct.lzma_allocator*, i8*, %struct.lzma_lz_options*)*) #4

; Function Attrs: nounwind uwtable
define internal i32 @lzma_encoder_init(%struct.lzma_lz_encoder* %lz, %struct.lzma_allocator* %allocator, i8* %options, %struct.lzma_lz_options* %lz_options) #0 !dbg !487 {
entry:
  %lz.addr = alloca %struct.lzma_lz_encoder*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %options.addr = alloca i8*, align 8
  %lz_options.addr = alloca %struct.lzma_lz_options*, align 8
  store %struct.lzma_lz_encoder* %lz, %struct.lzma_lz_encoder** %lz.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_lz_encoder** %lz.addr, metadata !1572, metadata !514), !dbg !1573
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !1574, metadata !514), !dbg !1575
  store i8* %options, i8** %options.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %options.addr, metadata !1576, metadata !514), !dbg !1577
  store %struct.lzma_lz_options* %lz_options, %struct.lzma_lz_options** %lz_options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_lz_options** %lz_options.addr, metadata !1578, metadata !514), !dbg !1579
  %0 = load %struct.lzma_lz_encoder*, %struct.lzma_lz_encoder** %lz.addr, align 8, !dbg !1580
  %code = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %0, i32 0, i32 1, !dbg !1581
  store i32 (%struct.lzma_coder_s*, %struct.lzma_mf_s*, i8*, i64*, i64)* @lzma_encode, i32 (%struct.lzma_coder_s*, %struct.lzma_mf_s*, i8*, i64*, i64)** %code, align 8, !dbg !1582
  %1 = load %struct.lzma_lz_encoder*, %struct.lzma_lz_encoder** %lz.addr, align 8, !dbg !1583
  %coder = getelementptr inbounds %struct.lzma_lz_encoder, %struct.lzma_lz_encoder* %1, i32 0, i32 0, !dbg !1584
  %2 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !1585
  %3 = load i8*, i8** %options.addr, align 8, !dbg !1586
  %4 = bitcast i8* %3 to %struct.lzma_options_lzma*, !dbg !1586
  %5 = load %struct.lzma_lz_options*, %struct.lzma_lz_options** %lz_options.addr, align 8, !dbg !1587
  %call = call i32 @lzma_lzma_encoder_create(%struct.lzma_coder_s** %coder, %struct.lzma_allocator* %2, %struct.lzma_options_lzma* %4, %struct.lzma_lz_options* %5), !dbg !1588
  ret i32 %call, !dbg !1589
}

; Function Attrs: nounwind uwtable
define i64 @lzma_lzma_encoder_memusage(i8* %options) #0 !dbg !383 {
entry:
  %retval = alloca i64, align 8
  %options.addr = alloca i8*, align 8
  %lz_options = alloca %struct.lzma_lz_options, align 8
  %lz_memusage = alloca i64, align 8
  store i8* %options, i8** %options.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %options.addr, metadata !1590, metadata !514), !dbg !1591
  call void @llvm.dbg.declare(metadata %struct.lzma_lz_options* %lz_options, metadata !1592, metadata !514), !dbg !1593
  call void @llvm.dbg.declare(metadata i64* %lz_memusage, metadata !1594, metadata !514), !dbg !1595
  %0 = load i8*, i8** %options.addr, align 8, !dbg !1596
  %1 = bitcast i8* %0 to %struct.lzma_options_lzma*, !dbg !1596
  %call = call zeroext i1 @is_options_valid(%struct.lzma_options_lzma* %1), !dbg !1598
  br i1 %call, label %if.end, label %if.then, !dbg !1599

if.then:                                          ; preds = %entry
  store i64 -1, i64* %retval, align 8, !dbg !1600
  br label %return, !dbg !1600

if.end:                                           ; preds = %entry
  %2 = load i8*, i8** %options.addr, align 8, !dbg !1601
  %3 = bitcast i8* %2 to %struct.lzma_options_lzma*, !dbg !1601
  call void @set_lz_options(%struct.lzma_lz_options* %lz_options, %struct.lzma_options_lzma* %3), !dbg !1602
  %call1 = call i64 @lzma_lz_encoder_memusage(%struct.lzma_lz_options* %lz_options), !dbg !1603
  store i64 %call1, i64* %lz_memusage, align 8, !dbg !1604
  %4 = load i64, i64* %lz_memusage, align 8, !dbg !1605
  %cmp = icmp eq i64 %4, -1, !dbg !1607
  br i1 %cmp, label %if.then2, label %if.end3, !dbg !1608

if.then2:                                         ; preds = %if.end
  store i64 -1, i64* %retval, align 8, !dbg !1609
  br label %return, !dbg !1609

if.end3:                                          ; preds = %if.end
  %5 = load i64, i64* %lz_memusage, align 8, !dbg !1610
  %add = add i64 249576, %5, !dbg !1611
  store i64 %add, i64* %retval, align 8, !dbg !1612
  br label %return, !dbg !1612

return:                                           ; preds = %if.end3, %if.then2, %if.then
  %6 = load i64, i64* %retval, align 8, !dbg !1613
  ret i64 %6, !dbg !1613
}

declare i64 @lzma_lz_encoder_memusage(%struct.lzma_lz_options*) #4

; Function Attrs: nounwind uwtable
define zeroext i1 @lzma_lzma_lclppb_encode(%struct.lzma_options_lzma* %options, i8* %byte) #0 !dbg !388 {
entry:
  %retval = alloca i1, align 1
  %options.addr = alloca %struct.lzma_options_lzma*, align 8
  %byte.addr = alloca i8*, align 8
  store %struct.lzma_options_lzma* %options, %struct.lzma_options_lzma** %options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_options_lzma** %options.addr, metadata !1614, metadata !514), !dbg !1615
  store i8* %byte, i8** %byte.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %byte.addr, metadata !1616, metadata !514), !dbg !1617
  %0 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1618
  %call = call zeroext i1 @is_lclppb_valid(%struct.lzma_options_lzma* %0), !dbg !1620
  br i1 %call, label %if.end, label %if.then, !dbg !1621

if.then:                                          ; preds = %entry
  store i1 true, i1* %retval, align 1, !dbg !1622
  br label %return, !dbg !1622

if.end:                                           ; preds = %entry
  %1 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1623
  %pb = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %1, i32 0, i32 5, !dbg !1624
  %2 = load i32, i32* %pb, align 4, !dbg !1624
  %mul = mul i32 %2, 5, !dbg !1625
  %3 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1626
  %lp = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %3, i32 0, i32 4, !dbg !1627
  %4 = load i32, i32* %lp, align 8, !dbg !1627
  %add = add i32 %mul, %4, !dbg !1628
  %mul1 = mul i32 %add, 9, !dbg !1629
  %5 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1630
  %lc = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %5, i32 0, i32 3, !dbg !1631
  %6 = load i32, i32* %lc, align 4, !dbg !1631
  %add2 = add i32 %mul1, %6, !dbg !1632
  %conv = trunc i32 %add2 to i8, !dbg !1633
  %7 = load i8*, i8** %byte.addr, align 8, !dbg !1634
  store i8 %conv, i8* %7, align 1, !dbg !1635
  %8 = load i8*, i8** %byte.addr, align 8, !dbg !1636
  %9 = load i8, i8* %8, align 1, !dbg !1636
  %conv3 = zext i8 %9 to i32, !dbg !1636
  %cmp = icmp sle i32 %conv3, 224, !dbg !1636
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1636

cond.true:                                        ; preds = %if.end
  br label %cond.end, !dbg !1637

cond.false:                                       ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([82 x i8], [82 x i8]* @.str.1, i32 0, i32 0), i32 669, i8* getelementptr inbounds ([68 x i8], [68 x i8]* @__PRETTY_FUNCTION__.lzma_lzma_lclppb_encode, i32 0, i32 0)) #6, !dbg !1639
  unreachable, !dbg !1639
                                                  ; No predecessors!
  br label %cond.end, !dbg !1641

cond.end:                                         ; preds = %10, %cond.true
  store i1 false, i1* %retval, align 1, !dbg !1643
  br label %return, !dbg !1643

return:                                           ; preds = %cond.end, %if.then
  %11 = load i1, i1* %retval, align 1, !dbg !1644
  ret i1 %11, !dbg !1644
}

; Function Attrs: inlinehint nounwind uwtable
define internal zeroext i1 @is_lclppb_valid(%struct.lzma_options_lzma* %options) #2 !dbg !505 {
entry:
  %options.addr = alloca %struct.lzma_options_lzma*, align 8
  store %struct.lzma_options_lzma* %options, %struct.lzma_options_lzma** %options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_options_lzma** %options.addr, metadata !1645, metadata !514), !dbg !1646
  %0 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1647
  %lc = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %0, i32 0, i32 3, !dbg !1648
  %1 = load i32, i32* %lc, align 4, !dbg !1648
  %cmp = icmp ule i32 %1, 4, !dbg !1649
  br i1 %cmp, label %land.lhs.true, label %land.end, !dbg !1650

land.lhs.true:                                    ; preds = %entry
  %2 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1651
  %lp = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %2, i32 0, i32 4, !dbg !1653
  %3 = load i32, i32* %lp, align 8, !dbg !1653
  %cmp1 = icmp ule i32 %3, 4, !dbg !1654
  br i1 %cmp1, label %land.lhs.true2, label %land.end, !dbg !1655

land.lhs.true2:                                   ; preds = %land.lhs.true
  %4 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1656
  %lc3 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %4, i32 0, i32 3, !dbg !1657
  %5 = load i32, i32* %lc3, align 4, !dbg !1657
  %6 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1658
  %lp4 = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %6, i32 0, i32 4, !dbg !1659
  %7 = load i32, i32* %lp4, align 8, !dbg !1659
  %add = add i32 %5, %7, !dbg !1660
  %cmp5 = icmp ule i32 %add, 4, !dbg !1661
  br i1 %cmp5, label %land.rhs, label %land.end, !dbg !1662

land.rhs:                                         ; preds = %land.lhs.true2
  %8 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %options.addr, align 8, !dbg !1663
  %pb = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %8, i32 0, i32 5, !dbg !1664
  %9 = load i32, i32* %pb, align 4, !dbg !1664
  %cmp6 = icmp ule i32 %9, 4, !dbg !1665
  br label %land.end

land.end:                                         ; preds = %land.rhs, %land.lhs.true2, %land.lhs.true, %entry
  %10 = phi i1 [ false, %land.lhs.true2 ], [ false, %land.lhs.true ], [ false, %entry ], [ %cmp6, %land.rhs ]
  ret i1 %10, !dbg !1666
}

; Function Attrs: nounwind uwtable
define i32 @lzma_lzma_props_encode(i8* %options, i8* %out) #0 !dbg !391 {
entry:
  %retval = alloca i32, align 4
  %options.addr = alloca i8*, align 8
  %out.addr = alloca i8*, align 8
  %opt = alloca %struct.lzma_options_lzma*, align 8
  store i8* %options, i8** %options.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %options.addr, metadata !1668, metadata !514), !dbg !1669
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !1670, metadata !514), !dbg !1671
  call void @llvm.dbg.declare(metadata %struct.lzma_options_lzma** %opt, metadata !1672, metadata !514), !dbg !1674
  %0 = load i8*, i8** %options.addr, align 8, !dbg !1675
  %1 = bitcast i8* %0 to %struct.lzma_options_lzma*, !dbg !1675
  store %struct.lzma_options_lzma* %1, %struct.lzma_options_lzma** %opt, align 8, !dbg !1674
  %2 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %opt, align 8, !dbg !1676
  %3 = load i8*, i8** %out.addr, align 8, !dbg !1678
  %call = call zeroext i1 @lzma_lzma_lclppb_encode(%struct.lzma_options_lzma* %2, i8* %3), !dbg !1679
  br i1 %call, label %if.then, label %if.end, !dbg !1680

if.then:                                          ; preds = %entry
  store i32 11, i32* %retval, align 4, !dbg !1681
  br label %return, !dbg !1681

if.end:                                           ; preds = %entry
  %4 = load i8*, i8** %out.addr, align 8, !dbg !1682
  %add.ptr = getelementptr inbounds i8, i8* %4, i64 1, !dbg !1682
  %5 = load %struct.lzma_options_lzma*, %struct.lzma_options_lzma** %opt, align 8, !dbg !1682
  %dict_size = getelementptr inbounds %struct.lzma_options_lzma, %struct.lzma_options_lzma* %5, i32 0, i32 0, !dbg !1682
  %6 = load i32, i32* %dict_size, align 8, !dbg !1682
  call void @write32ne(i8* %add.ptr, i32 %6), !dbg !1682
  store i32 0, i32* %retval, align 4, !dbg !1683
  br label %return, !dbg !1683

return:                                           ; preds = %if.end, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !1684
  ret i32 %7, !dbg !1684
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @write32ne(i8* %buf, i32 %num) #2 !dbg !506 {
entry:
  %buf.addr = alloca i8*, align 8
  %num.addr = alloca i32, align 4
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !1685, metadata !514), !dbg !1686
  store i32 %num, i32* %num.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %num.addr, metadata !1687, metadata !514), !dbg !1688
  %0 = load i32, i32* %num.addr, align 4, !dbg !1689
  %1 = load i8*, i8** %buf.addr, align 8, !dbg !1690
  %2 = bitcast i8* %1 to i32*, !dbg !1691
  store i32 %0, i32* %2, align 4, !dbg !1692
  ret void, !dbg !1693
}

; Function Attrs: nounwind readnone uwtable
define zeroext i8 @lzma_mode_is_supported(i32 %mode) #5 !dbg !394 {
entry:
  %mode.addr = alloca i32, align 4
  store i32 %mode, i32* %mode.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %mode.addr, metadata !1694, metadata !514), !dbg !1695
  %0 = load i32, i32* %mode.addr, align 4, !dbg !1696
  %cmp = icmp eq i32 %0, 1, !dbg !1697
  br i1 %cmp, label %lor.end, label %lor.rhs, !dbg !1698

lor.rhs:                                          ; preds = %entry
  %1 = load i32, i32* %mode.addr, align 4, !dbg !1699
  %cmp1 = icmp eq i32 %1, 2, !dbg !1701
  br label %lor.end, !dbg !1702

lor.end:                                          ; preds = %lor.rhs, %entry
  %2 = phi i1 [ true, %entry ], [ %cmp1, %lor.rhs ]
  %lor.ext = zext i1 %2 to i32, !dbg !1703
  %conv = trunc i32 %lor.ext to i8, !dbg !1705
  ret i8 %conv, !dbg !1706
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @mf_skip(%struct.lzma_mf_s* %mf, i32 %amount) #2 !dbg !401 {
entry:
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %amount.addr = alloca i32, align 4
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !1707, metadata !514), !dbg !1708
  store i32 %amount, i32* %amount.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %amount.addr, metadata !1709, metadata !514), !dbg !1710
  %0 = load i32, i32* %amount.addr, align 4, !dbg !1711
  %cmp = icmp ne i32 %0, 0, !dbg !1713
  br i1 %cmp, label %if.then, label %if.end, !dbg !1714

if.then:                                          ; preds = %entry
  %1 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1715
  %skip = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %1, i32 0, i32 11, !dbg !1717
  %2 = load void (%struct.lzma_mf_s*, i32)*, void (%struct.lzma_mf_s*, i32)** %skip, align 8, !dbg !1717
  %3 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1718
  %4 = load i32, i32* %amount.addr, align 4, !dbg !1719
  call void %2(%struct.lzma_mf_s* %3, i32 %4), !dbg !1715
  %5 = load i32, i32* %amount.addr, align 4, !dbg !1720
  %6 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1721
  %read_ahead = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %6, i32 0, i32 6, !dbg !1722
  %7 = load i32, i32* %read_ahead, align 4, !dbg !1723
  %add = add i32 %7, %5, !dbg !1723
  store i32 %add, i32* %read_ahead, align 4, !dbg !1723
  br label %if.end, !dbg !1724

if.end:                                           ; preds = %if.then, %entry
  ret void, !dbg !1725
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @rc_bit(%struct.lzma_range_encoder* %rc, i16* %prob, i32 %bit) #2 !dbg !402 {
entry:
  %rc.addr = alloca %struct.lzma_range_encoder*, align 8
  %prob.addr = alloca i16*, align 8
  %bit.addr = alloca i32, align 4
  store %struct.lzma_range_encoder* %rc, %struct.lzma_range_encoder** %rc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_range_encoder** %rc.addr, metadata !1726, metadata !514), !dbg !1727
  store i16* %prob, i16** %prob.addr, align 8
  call void @llvm.dbg.declare(metadata i16** %prob.addr, metadata !1728, metadata !514), !dbg !1729
  store i32 %bit, i32* %bit.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %bit.addr, metadata !1730, metadata !514), !dbg !1731
  %0 = load i32, i32* %bit.addr, align 4, !dbg !1732
  %1 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1733
  %count = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %1, i32 0, i32 4, !dbg !1734
  %2 = load i64, i64* %count, align 8, !dbg !1734
  %3 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1735
  %symbols = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %3, i32 0, i32 6, !dbg !1736
  %arrayidx = getelementptr inbounds [58 x i32], [58 x i32]* %symbols, i64 0, i64 %2, !dbg !1735
  store i32 %0, i32* %arrayidx, align 4, !dbg !1737
  %4 = load i16*, i16** %prob.addr, align 8, !dbg !1738
  %5 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1739
  %count1 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %5, i32 0, i32 4, !dbg !1740
  %6 = load i64, i64* %count1, align 8, !dbg !1740
  %7 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1741
  %probs = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %7, i32 0, i32 7, !dbg !1742
  %arrayidx2 = getelementptr inbounds [58 x i16*], [58 x i16*]* %probs, i64 0, i64 %6, !dbg !1741
  store i16* %4, i16** %arrayidx2, align 8, !dbg !1743
  %8 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1744
  %count3 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %8, i32 0, i32 4, !dbg !1745
  %9 = load i64, i64* %count3, align 8, !dbg !1746
  %inc = add i64 %9, 1, !dbg !1746
  store i64 %inc, i64* %count3, align 8, !dbg !1746
  ret void, !dbg !1747
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @rc_bittree(%struct.lzma_range_encoder* %rc, i16* %probs, i32 %bit_count, i32 %symbol) #2 !dbg !406 {
entry:
  %rc.addr = alloca %struct.lzma_range_encoder*, align 8
  %probs.addr = alloca i16*, align 8
  %bit_count.addr = alloca i32, align 4
  %symbol.addr = alloca i32, align 4
  %model_index = alloca i32, align 4
  %bit = alloca i32, align 4
  store %struct.lzma_range_encoder* %rc, %struct.lzma_range_encoder** %rc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_range_encoder** %rc.addr, metadata !1748, metadata !514), !dbg !1749
  store i16* %probs, i16** %probs.addr, align 8
  call void @llvm.dbg.declare(metadata i16** %probs.addr, metadata !1750, metadata !514), !dbg !1751
  store i32 %bit_count, i32* %bit_count.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %bit_count.addr, metadata !1752, metadata !514), !dbg !1753
  store i32 %symbol, i32* %symbol.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %symbol.addr, metadata !1754, metadata !514), !dbg !1755
  call void @llvm.dbg.declare(metadata i32* %model_index, metadata !1756, metadata !514), !dbg !1757
  store i32 1, i32* %model_index, align 4, !dbg !1757
  br label %do.body, !dbg !1758

do.body:                                          ; preds = %do.cond, %entry
  call void @llvm.dbg.declare(metadata i32* %bit, metadata !1759, metadata !514), !dbg !1761
  %0 = load i32, i32* %symbol.addr, align 4, !dbg !1762
  %1 = load i32, i32* %bit_count.addr, align 4, !dbg !1763
  %dec = add i32 %1, -1, !dbg !1763
  store i32 %dec, i32* %bit_count.addr, align 4, !dbg !1763
  %shr = lshr i32 %0, %dec, !dbg !1764
  %and = and i32 %shr, 1, !dbg !1765
  store i32 %and, i32* %bit, align 4, !dbg !1761
  %2 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1766
  %3 = load i32, i32* %model_index, align 4, !dbg !1767
  %idxprom = zext i32 %3 to i64, !dbg !1768
  %4 = load i16*, i16** %probs.addr, align 8, !dbg !1768
  %arrayidx = getelementptr inbounds i16, i16* %4, i64 %idxprom, !dbg !1768
  %5 = load i32, i32* %bit, align 4, !dbg !1769
  call void @rc_bit(%struct.lzma_range_encoder* %2, i16* %arrayidx, i32 %5), !dbg !1770
  %6 = load i32, i32* %model_index, align 4, !dbg !1771
  %shl = shl i32 %6, 1, !dbg !1772
  %7 = load i32, i32* %bit, align 4, !dbg !1773
  %add = add i32 %shl, %7, !dbg !1774
  store i32 %add, i32* %model_index, align 4, !dbg !1775
  br label %do.cond, !dbg !1776

do.cond:                                          ; preds = %do.body
  %8 = load i32, i32* %bit_count.addr, align 4, !dbg !1777
  %cmp = icmp ne i32 %8, 0, !dbg !1779
  br i1 %cmp, label %do.body, label %do.end, !dbg !1780

do.end:                                           ; preds = %do.cond
  ret void, !dbg !1781
}

; Function Attrs: inlinehint nounwind uwtable
define internal zeroext i1 @rc_shift_low(%struct.lzma_range_encoder* %rc, i8* %out, i64* %out_pos, i64 %out_size) #2 !dbg !417 {
entry:
  %retval = alloca i1, align 1
  %rc.addr = alloca %struct.lzma_range_encoder*, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  store %struct.lzma_range_encoder* %rc, %struct.lzma_range_encoder** %rc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_range_encoder** %rc.addr, metadata !1782, metadata !514), !dbg !1783
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !1784, metadata !514), !dbg !1785
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !1786, metadata !514), !dbg !1787
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !1788, metadata !514), !dbg !1789
  %0 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1790
  %low = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %0, i32 0, i32 0, !dbg !1792
  %1 = load i64, i64* %low, align 8, !dbg !1792
  %conv = trunc i64 %1 to i32, !dbg !1793
  %cmp = icmp ult i32 %conv, -16777216, !dbg !1794
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !1795

lor.lhs.false:                                    ; preds = %entry
  %2 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1796
  %low2 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %2, i32 0, i32 0, !dbg !1798
  %3 = load i64, i64* %low2, align 8, !dbg !1798
  %shr = lshr i64 %3, 32, !dbg !1799
  %conv3 = trunc i64 %shr to i32, !dbg !1800
  %cmp4 = icmp ne i32 %conv3, 0, !dbg !1801
  br i1 %cmp4, label %if.then, label %if.end22, !dbg !1802

if.then:                                          ; preds = %lor.lhs.false, %entry
  br label %do.body, !dbg !1804

do.body:                                          ; preds = %do.cond, %if.then
  %4 = load i64*, i64** %out_pos.addr, align 8, !dbg !1806
  %5 = load i64, i64* %4, align 8, !dbg !1809
  %6 = load i64, i64* %out_size.addr, align 8, !dbg !1810
  %cmp6 = icmp eq i64 %5, %6, !dbg !1811
  br i1 %cmp6, label %if.then8, label %if.end, !dbg !1812

if.then8:                                         ; preds = %do.body
  store i1 true, i1* %retval, align 1, !dbg !1813
  br label %return, !dbg !1813

if.end:                                           ; preds = %do.body
  %7 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1814
  %cache = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %7, i32 0, i32 3, !dbg !1815
  %8 = load i8, i8* %cache, align 4, !dbg !1815
  %conv9 = zext i8 %8 to i32, !dbg !1814
  %9 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1816
  %low10 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %9, i32 0, i32 0, !dbg !1817
  %10 = load i64, i64* %low10, align 8, !dbg !1817
  %shr11 = lshr i64 %10, 32, !dbg !1818
  %conv12 = trunc i64 %shr11 to i8, !dbg !1819
  %conv13 = zext i8 %conv12 to i32, !dbg !1819
  %add = add nsw i32 %conv9, %conv13, !dbg !1820
  %conv14 = trunc i32 %add to i8, !dbg !1814
  %11 = load i64*, i64** %out_pos.addr, align 8, !dbg !1821
  %12 = load i64, i64* %11, align 8, !dbg !1822
  %13 = load i8*, i8** %out.addr, align 8, !dbg !1823
  %arrayidx = getelementptr inbounds i8, i8* %13, i64 %12, !dbg !1823
  store i8 %conv14, i8* %arrayidx, align 1, !dbg !1824
  %14 = load i64*, i64** %out_pos.addr, align 8, !dbg !1825
  %15 = load i64, i64* %14, align 8, !dbg !1826
  %inc = add i64 %15, 1, !dbg !1826
  store i64 %inc, i64* %14, align 8, !dbg !1826
  %16 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1827
  %cache15 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %16, i32 0, i32 3, !dbg !1828
  store i8 -1, i8* %cache15, align 4, !dbg !1829
  br label %do.cond, !dbg !1830

do.cond:                                          ; preds = %if.end
  %17 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1831
  %cache_size = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %17, i32 0, i32 1, !dbg !1833
  %18 = load i64, i64* %cache_size, align 8, !dbg !1834
  %dec = add i64 %18, -1, !dbg !1834
  store i64 %dec, i64* %cache_size, align 8, !dbg !1834
  %cmp16 = icmp ne i64 %dec, 0, !dbg !1835
  br i1 %cmp16, label %do.body, label %do.end, !dbg !1836

do.end:                                           ; preds = %do.cond
  %19 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1837
  %low18 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %19, i32 0, i32 0, !dbg !1838
  %20 = load i64, i64* %low18, align 8, !dbg !1838
  %shr19 = lshr i64 %20, 24, !dbg !1839
  %and = and i64 %shr19, 255, !dbg !1840
  %conv20 = trunc i64 %and to i8, !dbg !1841
  %21 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1842
  %cache21 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %21, i32 0, i32 3, !dbg !1843
  store i8 %conv20, i8* %cache21, align 4, !dbg !1844
  br label %if.end22, !dbg !1845

if.end22:                                         ; preds = %do.end, %lor.lhs.false
  %22 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1846
  %cache_size23 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %22, i32 0, i32 1, !dbg !1847
  %23 = load i64, i64* %cache_size23, align 8, !dbg !1848
  %inc24 = add i64 %23, 1, !dbg !1848
  store i64 %inc24, i64* %cache_size23, align 8, !dbg !1848
  %24 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1849
  %low25 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %24, i32 0, i32 0, !dbg !1850
  %25 = load i64, i64* %low25, align 8, !dbg !1850
  %and26 = and i64 %25, 16777215, !dbg !1851
  %shl = shl i64 %and26, 8, !dbg !1852
  %26 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !1853
  %low27 = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %26, i32 0, i32 0, !dbg !1854
  store i64 %shl, i64* %low27, align 8, !dbg !1855
  store i1 false, i1* %retval, align 1, !dbg !1856
  br label %return, !dbg !1856

return:                                           ; preds = %if.end22, %if.then8
  %27 = load i1, i1* %retval, align 1, !dbg !1857
  ret i1 %27, !dbg !1857
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @literal(%struct.lzma_coder_s* %coder, %struct.lzma_mf_s* %mf, i32 %position) #2 !dbg !426 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %position.addr = alloca i32, align 4
  %cur_byte = alloca i8, align 1
  %subcoder = alloca i16*, align 8
  %match_byte = alloca i8, align 1
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !1858, metadata !514), !dbg !1859
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !1860, metadata !514), !dbg !1861
  store i32 %position, i32* %position.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %position.addr, metadata !1862, metadata !514), !dbg !1863
  call void @llvm.dbg.declare(metadata i8* %cur_byte, metadata !1864, metadata !514), !dbg !1865
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1866
  %read_pos = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %0, i32 0, i32 5, !dbg !1867
  %1 = load i32, i32* %read_pos, align 8, !dbg !1867
  %2 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1868
  %read_ahead = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %2, i32 0, i32 6, !dbg !1869
  %3 = load i32, i32* %read_ahead, align 4, !dbg !1869
  %sub = sub i32 %1, %3, !dbg !1870
  %idxprom = zext i32 %sub to i64, !dbg !1871
  %4 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1871
  %buffer = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %4, i32 0, i32 0, !dbg !1872
  %5 = load i8*, i8** %buffer, align 8, !dbg !1872
  %arrayidx = getelementptr inbounds i8, i8* %5, i64 %idxprom, !dbg !1871
  %6 = load i8, i8* %arrayidx, align 1, !dbg !1871
  store i8 %6, i8* %cur_byte, align 1, !dbg !1865
  call void @llvm.dbg.declare(metadata i16** %subcoder, metadata !1873, metadata !514), !dbg !1874
  %7 = load i32, i32* %position.addr, align 4, !dbg !1875
  %8 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1875
  %literal_pos_mask = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %8, i32 0, i32 11, !dbg !1875
  %9 = load i32, i32* %literal_pos_mask, align 8, !dbg !1875
  %and = and i32 %7, %9, !dbg !1875
  %10 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1875
  %literal_context_bits = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %10, i32 0, i32 10, !dbg !1875
  %11 = load i32, i32* %literal_context_bits, align 4, !dbg !1875
  %shl = shl i32 %and, %11, !dbg !1875
  %12 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1875
  %read_pos1 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %12, i32 0, i32 5, !dbg !1875
  %13 = load i32, i32* %read_pos1, align 8, !dbg !1875
  %14 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1875
  %read_ahead2 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %14, i32 0, i32 6, !dbg !1875
  %15 = load i32, i32* %read_ahead2, align 4, !dbg !1875
  %sub3 = sub i32 %13, %15, !dbg !1875
  %sub4 = sub i32 %sub3, 1, !dbg !1875
  %idxprom5 = zext i32 %sub4 to i64, !dbg !1875
  %16 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1875
  %buffer6 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %16, i32 0, i32 0, !dbg !1875
  %17 = load i8*, i8** %buffer6, align 8, !dbg !1875
  %arrayidx7 = getelementptr inbounds i8, i8* %17, i64 %idxprom5, !dbg !1875
  %18 = load i8, i8* %arrayidx7, align 1, !dbg !1875
  %conv = zext i8 %18 to i32, !dbg !1875
  %19 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1875
  %literal_context_bits8 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %19, i32 0, i32 10, !dbg !1875
  %20 = load i32, i32* %literal_context_bits8, align 4, !dbg !1875
  %sub9 = sub i32 8, %20, !dbg !1875
  %shr = ashr i32 %conv, %sub9, !dbg !1875
  %add = add i32 %shl, %shr, !dbg !1875
  %idxprom10 = zext i32 %add to i64, !dbg !1875
  %21 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1875
  %literal = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %21, i32 0, i32 12, !dbg !1875
  %arrayidx11 = getelementptr inbounds [16 x [768 x i16]], [16 x [768 x i16]]* %literal, i64 0, i64 %idxprom10, !dbg !1875
  %arraydecay = getelementptr inbounds [768 x i16], [768 x i16]* %arrayidx11, i32 0, i32 0, !dbg !1875
  store i16* %arraydecay, i16** %subcoder, align 8, !dbg !1874
  %22 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1876
  %state = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %22, i32 0, i32 1, !dbg !1876
  %23 = load i32, i32* %state, align 8, !dbg !1876
  %cmp = icmp ult i32 %23, 7, !dbg !1876
  br i1 %cmp, label %if.then, label %if.else, !dbg !1878

if.then:                                          ; preds = %entry
  %24 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1879
  %rc = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %24, i32 0, i32 0, !dbg !1881
  %25 = load i16*, i16** %subcoder, align 8, !dbg !1882
  %26 = load i8, i8* %cur_byte, align 1, !dbg !1883
  %conv13 = zext i8 %26 to i32, !dbg !1883
  call void @rc_bittree(%struct.lzma_range_encoder* %rc, i16* %25, i32 8, i32 %conv13), !dbg !1884
  br label %if.end, !dbg !1885

if.else:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i8* %match_byte, metadata !1886, metadata !514), !dbg !1888
  %27 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1889
  %read_pos14 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %27, i32 0, i32 5, !dbg !1890
  %28 = load i32, i32* %read_pos14, align 8, !dbg !1890
  %29 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1891
  %reps = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %29, i32 0, i32 2, !dbg !1892
  %arrayidx15 = getelementptr inbounds [4 x i32], [4 x i32]* %reps, i64 0, i64 0, !dbg !1891
  %30 = load i32, i32* %arrayidx15, align 4, !dbg !1891
  %sub16 = sub i32 %28, %30, !dbg !1893
  %sub17 = sub i32 %sub16, 1, !dbg !1894
  %31 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1895
  %read_ahead18 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %31, i32 0, i32 6, !dbg !1896
  %32 = load i32, i32* %read_ahead18, align 4, !dbg !1896
  %sub19 = sub i32 %sub17, %32, !dbg !1897
  %idxprom20 = zext i32 %sub19 to i64, !dbg !1898
  %33 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !1898
  %buffer21 = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %33, i32 0, i32 0, !dbg !1899
  %34 = load i8*, i8** %buffer21, align 8, !dbg !1899
  %arrayidx22 = getelementptr inbounds i8, i8* %34, i64 %idxprom20, !dbg !1898
  %35 = load i8, i8* %arrayidx22, align 1, !dbg !1898
  store i8 %35, i8* %match_byte, align 1, !dbg !1888
  %36 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1900
  %rc23 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %36, i32 0, i32 0, !dbg !1901
  %37 = load i16*, i16** %subcoder, align 8, !dbg !1902
  %38 = load i8, i8* %match_byte, align 1, !dbg !1903
  %conv24 = zext i8 %38 to i32, !dbg !1903
  %39 = load i8, i8* %cur_byte, align 1, !dbg !1904
  %conv25 = zext i8 %39 to i32, !dbg !1904
  call void @literal_matched(%struct.lzma_range_encoder* %rc23, i16* %37, i32 %conv24, i32 %conv25), !dbg !1905
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %40 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1906
  %state26 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %40, i32 0, i32 1, !dbg !1906
  %41 = load i32, i32* %state26, align 8, !dbg !1906
  %cmp27 = icmp ule i32 %41, 3, !dbg !1906
  br i1 %cmp27, label %cond.true, label %cond.false, !dbg !1906

cond.true:                                        ; preds = %if.end
  br label %cond.end38, !dbg !1907

cond.false:                                       ; preds = %if.end
  %42 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1909
  %state29 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %42, i32 0, i32 1, !dbg !1909
  %43 = load i32, i32* %state29, align 8, !dbg !1909
  %cmp30 = icmp ule i32 %43, 9, !dbg !1909
  br i1 %cmp30, label %cond.true32, label %cond.false35, !dbg !1909

cond.true32:                                      ; preds = %cond.false
  %44 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1911
  %state33 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %44, i32 0, i32 1, !dbg !1911
  %45 = load i32, i32* %state33, align 8, !dbg !1911
  %sub34 = sub i32 %45, 3, !dbg !1911
  br label %cond.end, !dbg !1911

cond.false35:                                     ; preds = %cond.false
  %46 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1913
  %state36 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %46, i32 0, i32 1, !dbg !1913
  %47 = load i32, i32* %state36, align 8, !dbg !1913
  %sub37 = sub i32 %47, 6, !dbg !1913
  br label %cond.end, !dbg !1913

cond.end:                                         ; preds = %cond.false35, %cond.true32
  %cond = phi i32 [ %sub34, %cond.true32 ], [ %sub37, %cond.false35 ], !dbg !1915
  br label %cond.end38, !dbg !1915

cond.end38:                                       ; preds = %cond.end, %cond.true
  %cond39 = phi i32 [ 0, %cond.true ], [ %cond, %cond.end ], !dbg !1917
  %48 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1917
  %state40 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %48, i32 0, i32 1, !dbg !1917
  store i32 %cond39, i32* %state40, align 8, !dbg !1917
  ret void, !dbg !1919
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @rep_match(%struct.lzma_coder_s* %coder, i32 %pos_state, i32 %rep, i32 %len) #2 !dbg !430 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %pos_state.addr = alloca i32, align 4
  %rep.addr = alloca i32, align 4
  %len.addr = alloca i32, align 4
  %distance = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !1920, metadata !514), !dbg !1921
  store i32 %pos_state, i32* %pos_state.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %pos_state.addr, metadata !1922, metadata !514), !dbg !1923
  store i32 %rep, i32* %rep.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %rep.addr, metadata !1924, metadata !514), !dbg !1925
  store i32 %len, i32* %len.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len.addr, metadata !1926, metadata !514), !dbg !1927
  %0 = load i32, i32* %rep.addr, align 4, !dbg !1928
  %cmp = icmp eq i32 %0, 0, !dbg !1930
  br i1 %cmp, label %if.then, label %if.else, !dbg !1931

if.then:                                          ; preds = %entry
  %1 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1932
  %rc = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %1, i32 0, i32 0, !dbg !1934
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1935
  %state = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 1, !dbg !1936
  %3 = load i32, i32* %state, align 8, !dbg !1936
  %idxprom = zext i32 %3 to i64, !dbg !1937
  %4 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1937
  %is_rep0 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %4, i32 0, i32 15, !dbg !1938
  %arrayidx = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep0, i64 0, i64 %idxprom, !dbg !1937
  call void @rc_bit(%struct.lzma_range_encoder* %rc, i16* %arrayidx, i32 0), !dbg !1939
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1940
  %rc1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 0, !dbg !1941
  %6 = load i32, i32* %pos_state.addr, align 4, !dbg !1942
  %idxprom2 = zext i32 %6 to i64, !dbg !1943
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1944
  %state3 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %7, i32 0, i32 1, !dbg !1945
  %8 = load i32, i32* %state3, align 8, !dbg !1945
  %idxprom4 = zext i32 %8 to i64, !dbg !1943
  %9 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1943
  %is_rep0_long = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %9, i32 0, i32 18, !dbg !1946
  %arrayidx5 = getelementptr inbounds [12 x [16 x i16]], [12 x [16 x i16]]* %is_rep0_long, i64 0, i64 %idxprom4, !dbg !1943
  %arrayidx6 = getelementptr inbounds [16 x i16], [16 x i16]* %arrayidx5, i64 0, i64 %idxprom2, !dbg !1943
  %10 = load i32, i32* %len.addr, align 4, !dbg !1947
  %cmp7 = icmp ne i32 %10, 1, !dbg !1948
  %conv = zext i1 %cmp7 to i32, !dbg !1948
  call void @rc_bit(%struct.lzma_range_encoder* %rc1, i16* %arrayidx6, i32 %conv), !dbg !1949
  br label %if.end50, !dbg !1950

if.else:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %distance, metadata !1951, metadata !514), !dbg !1953
  %11 = load i32, i32* %rep.addr, align 4, !dbg !1954
  %idxprom8 = zext i32 %11 to i64, !dbg !1955
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1955
  %reps = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %12, i32 0, i32 2, !dbg !1956
  %arrayidx9 = getelementptr inbounds [4 x i32], [4 x i32]* %reps, i64 0, i64 %idxprom8, !dbg !1955
  %13 = load i32, i32* %arrayidx9, align 4, !dbg !1955
  store i32 %13, i32* %distance, align 4, !dbg !1953
  %14 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1957
  %rc10 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %14, i32 0, i32 0, !dbg !1958
  %15 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1959
  %state11 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %15, i32 0, i32 1, !dbg !1960
  %16 = load i32, i32* %state11, align 8, !dbg !1960
  %idxprom12 = zext i32 %16 to i64, !dbg !1961
  %17 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1961
  %is_rep013 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %17, i32 0, i32 15, !dbg !1962
  %arrayidx14 = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep013, i64 0, i64 %idxprom12, !dbg !1961
  call void @rc_bit(%struct.lzma_range_encoder* %rc10, i16* %arrayidx14, i32 1), !dbg !1963
  %18 = load i32, i32* %rep.addr, align 4, !dbg !1964
  %cmp15 = icmp eq i32 %18, 1, !dbg !1966
  br i1 %cmp15, label %if.then17, label %if.else22, !dbg !1967

if.then17:                                        ; preds = %if.else
  %19 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1968
  %rc18 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %19, i32 0, i32 0, !dbg !1970
  %20 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1971
  %state19 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %20, i32 0, i32 1, !dbg !1972
  %21 = load i32, i32* %state19, align 8, !dbg !1972
  %idxprom20 = zext i32 %21 to i64, !dbg !1973
  %22 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1973
  %is_rep1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %22, i32 0, i32 16, !dbg !1974
  %arrayidx21 = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep1, i64 0, i64 %idxprom20, !dbg !1973
  call void @rc_bit(%struct.lzma_range_encoder* %rc18, i16* %arrayidx21, i32 0), !dbg !1975
  br label %if.end43, !dbg !1976

if.else22:                                        ; preds = %if.else
  %23 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1977
  %rc23 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %23, i32 0, i32 0, !dbg !1979
  %24 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1980
  %state24 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %24, i32 0, i32 1, !dbg !1981
  %25 = load i32, i32* %state24, align 8, !dbg !1981
  %idxprom25 = zext i32 %25 to i64, !dbg !1982
  %26 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1982
  %is_rep126 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %26, i32 0, i32 16, !dbg !1983
  %arrayidx27 = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep126, i64 0, i64 %idxprom25, !dbg !1982
  call void @rc_bit(%struct.lzma_range_encoder* %rc23, i16* %arrayidx27, i32 1), !dbg !1984
  %27 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1985
  %rc28 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %27, i32 0, i32 0, !dbg !1986
  %28 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1987
  %state29 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %28, i32 0, i32 1, !dbg !1988
  %29 = load i32, i32* %state29, align 8, !dbg !1988
  %idxprom30 = zext i32 %29 to i64, !dbg !1989
  %30 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1989
  %is_rep2 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %30, i32 0, i32 17, !dbg !1990
  %arrayidx31 = getelementptr inbounds [12 x i16], [12 x i16]* %is_rep2, i64 0, i64 %idxprom30, !dbg !1989
  %31 = load i32, i32* %rep.addr, align 4, !dbg !1991
  %sub = sub i32 %31, 2, !dbg !1992
  call void @rc_bit(%struct.lzma_range_encoder* %rc28, i16* %arrayidx31, i32 %sub), !dbg !1993
  %32 = load i32, i32* %rep.addr, align 4, !dbg !1994
  %cmp32 = icmp eq i32 %32, 3, !dbg !1996
  br i1 %cmp32, label %if.then34, label %if.end, !dbg !1997

if.then34:                                        ; preds = %if.else22
  %33 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !1998
  %reps35 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %33, i32 0, i32 2, !dbg !1999
  %arrayidx36 = getelementptr inbounds [4 x i32], [4 x i32]* %reps35, i64 0, i64 2, !dbg !1998
  %34 = load i32, i32* %arrayidx36, align 4, !dbg !1998
  %35 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2000
  %reps37 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %35, i32 0, i32 2, !dbg !2001
  %arrayidx38 = getelementptr inbounds [4 x i32], [4 x i32]* %reps37, i64 0, i64 3, !dbg !2000
  store i32 %34, i32* %arrayidx38, align 4, !dbg !2002
  br label %if.end, !dbg !2000

if.end:                                           ; preds = %if.then34, %if.else22
  %36 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2003
  %reps39 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %36, i32 0, i32 2, !dbg !2004
  %arrayidx40 = getelementptr inbounds [4 x i32], [4 x i32]* %reps39, i64 0, i64 1, !dbg !2003
  %37 = load i32, i32* %arrayidx40, align 4, !dbg !2003
  %38 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2005
  %reps41 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %38, i32 0, i32 2, !dbg !2006
  %arrayidx42 = getelementptr inbounds [4 x i32], [4 x i32]* %reps41, i64 0, i64 2, !dbg !2005
  store i32 %37, i32* %arrayidx42, align 4, !dbg !2007
  br label %if.end43

if.end43:                                         ; preds = %if.end, %if.then17
  %39 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2008
  %reps44 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %39, i32 0, i32 2, !dbg !2009
  %arrayidx45 = getelementptr inbounds [4 x i32], [4 x i32]* %reps44, i64 0, i64 0, !dbg !2008
  %40 = load i32, i32* %arrayidx45, align 4, !dbg !2008
  %41 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2010
  %reps46 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %41, i32 0, i32 2, !dbg !2011
  %arrayidx47 = getelementptr inbounds [4 x i32], [4 x i32]* %reps46, i64 0, i64 1, !dbg !2010
  store i32 %40, i32* %arrayidx47, align 4, !dbg !2012
  %42 = load i32, i32* %distance, align 4, !dbg !2013
  %43 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2014
  %reps48 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %43, i32 0, i32 2, !dbg !2015
  %arrayidx49 = getelementptr inbounds [4 x i32], [4 x i32]* %reps48, i64 0, i64 0, !dbg !2014
  store i32 %42, i32* %arrayidx49, align 4, !dbg !2016
  br label %if.end50

if.end50:                                         ; preds = %if.end43, %if.then
  %44 = load i32, i32* %len.addr, align 4, !dbg !2017
  %cmp51 = icmp eq i32 %44, 1, !dbg !2019
  br i1 %cmp51, label %if.then53, label %if.else58, !dbg !2020

if.then53:                                        ; preds = %if.end50
  %45 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2021
  %state54 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %45, i32 0, i32 1, !dbg !2021
  %46 = load i32, i32* %state54, align 8, !dbg !2021
  %cmp55 = icmp ult i32 %46, 7, !dbg !2021
  %cond = select i1 %cmp55, i32 9, i32 11, !dbg !2021
  %47 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2021
  %state57 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %47, i32 0, i32 1, !dbg !2021
  store i32 %cond, i32* %state57, align 8, !dbg !2021
  br label %if.end65, !dbg !2023

if.else58:                                        ; preds = %if.end50
  %48 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2024
  %rc59 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %48, i32 0, i32 0, !dbg !2026
  %49 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2027
  %rep_len_encoder = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %49, i32 0, i32 23, !dbg !2028
  %50 = load i32, i32* %pos_state.addr, align 4, !dbg !2029
  %51 = load i32, i32* %len.addr, align 4, !dbg !2030
  %52 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2031
  %fast_mode = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %52, i32 0, i32 6, !dbg !2032
  %53 = load i8, i8* %fast_mode, align 4, !dbg !2032
  %tobool = trunc i8 %53 to i1, !dbg !2032
  call void @length(%struct.lzma_range_encoder* %rc59, %struct.lzma_length_encoder* %rep_len_encoder, i32 %50, i32 %51, i1 zeroext %tobool), !dbg !2033
  %54 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2034
  %state60 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %54, i32 0, i32 1, !dbg !2034
  %55 = load i32, i32* %state60, align 8, !dbg !2034
  %cmp61 = icmp ult i32 %55, 7, !dbg !2034
  %cond63 = select i1 %cmp61, i32 8, i32 11, !dbg !2034
  %56 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2034
  %state64 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %56, i32 0, i32 1, !dbg !2034
  store i32 %cond63, i32* %state64, align 8, !dbg !2034
  br label %if.end65

if.end65:                                         ; preds = %if.else58, %if.then53
  ret void, !dbg !2035
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @match(%struct.lzma_coder_s* %coder, i32 %pos_state, i32 %distance, i32 %len) #2 !dbg !456 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %pos_state.addr = alloca i32, align 4
  %distance.addr = alloca i32, align 4
  %len.addr = alloca i32, align 4
  %pos_slot = alloca i32, align 4
  %len_to_pos_state = alloca i32, align 4
  %footer_bits = alloca i32, align 4
  %base = alloca i32, align 4
  %pos_reduced = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !2036, metadata !514), !dbg !2037
  store i32 %pos_state, i32* %pos_state.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %pos_state.addr, metadata !2038, metadata !514), !dbg !2039
  store i32 %distance, i32* %distance.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %distance.addr, metadata !2040, metadata !514), !dbg !2041
  store i32 %len, i32* %len.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len.addr, metadata !2042, metadata !514), !dbg !2043
  call void @llvm.dbg.declare(metadata i32* %pos_slot, metadata !2044, metadata !514), !dbg !2045
  call void @llvm.dbg.declare(metadata i32* %len_to_pos_state, metadata !2046, metadata !514), !dbg !2047
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2048
  %state = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 1, !dbg !2048
  %1 = load i32, i32* %state, align 8, !dbg !2048
  %cmp = icmp ult i32 %1, 7, !dbg !2048
  %cond = select i1 %cmp, i32 7, i32 10, !dbg !2048
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2048
  %state1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 1, !dbg !2048
  store i32 %cond, i32* %state1, align 8, !dbg !2048
  %3 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2049
  %rc = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %3, i32 0, i32 0, !dbg !2050
  %4 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2051
  %match_len_encoder = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %4, i32 0, i32 22, !dbg !2052
  %5 = load i32, i32* %pos_state.addr, align 4, !dbg !2053
  %6 = load i32, i32* %len.addr, align 4, !dbg !2054
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2055
  %fast_mode = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %7, i32 0, i32 6, !dbg !2056
  %8 = load i8, i8* %fast_mode, align 4, !dbg !2056
  %tobool = trunc i8 %8 to i1, !dbg !2056
  call void @length(%struct.lzma_range_encoder* %rc, %struct.lzma_length_encoder* %match_len_encoder, i32 %5, i32 %6, i1 zeroext %tobool), !dbg !2057
  %9 = load i32, i32* %distance.addr, align 4, !dbg !2058
  %call = call i32 @get_pos_slot(i32 %9), !dbg !2059
  store i32 %call, i32* %pos_slot, align 4, !dbg !2060
  %10 = load i32, i32* %len.addr, align 4, !dbg !2061
  %cmp2 = icmp ult i32 %10, 6, !dbg !2061
  br i1 %cmp2, label %cond.true, label %cond.false, !dbg !2061

cond.true:                                        ; preds = %entry
  %11 = load i32, i32* %len.addr, align 4, !dbg !2062
  %sub = sub i32 %11, 2, !dbg !2062
  br label %cond.end, !dbg !2062

cond.false:                                       ; preds = %entry
  br label %cond.end, !dbg !2064

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond3 = phi i32 [ %sub, %cond.true ], [ 3, %cond.false ], !dbg !2066
  store i32 %cond3, i32* %len_to_pos_state, align 4, !dbg !2068
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2069
  %rc4 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %12, i32 0, i32 0, !dbg !2070
  %13 = load i32, i32* %len_to_pos_state, align 4, !dbg !2071
  %idxprom = zext i32 %13 to i64, !dbg !2072
  %14 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2072
  %pos_slot5 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %14, i32 0, i32 19, !dbg !2073
  %arrayidx = getelementptr inbounds [4 x [64 x i16]], [4 x [64 x i16]]* %pos_slot5, i64 0, i64 %idxprom, !dbg !2072
  %arraydecay = getelementptr inbounds [64 x i16], [64 x i16]* %arrayidx, i32 0, i32 0, !dbg !2072
  %15 = load i32, i32* %pos_slot, align 4, !dbg !2074
  call void @rc_bittree(%struct.lzma_range_encoder* %rc4, i16* %arraydecay, i32 6, i32 %15), !dbg !2075
  %16 = load i32, i32* %pos_slot, align 4, !dbg !2076
  %cmp6 = icmp uge i32 %16, 4, !dbg !2078
  br i1 %cmp6, label %if.then, label %if.end22, !dbg !2079

if.then:                                          ; preds = %cond.end
  call void @llvm.dbg.declare(metadata i32* %footer_bits, metadata !2080, metadata !514), !dbg !2082
  %17 = load i32, i32* %pos_slot, align 4, !dbg !2083
  %shr = lshr i32 %17, 1, !dbg !2084
  %sub7 = sub i32 %shr, 1, !dbg !2085
  store i32 %sub7, i32* %footer_bits, align 4, !dbg !2082
  call void @llvm.dbg.declare(metadata i32* %base, metadata !2086, metadata !514), !dbg !2087
  %18 = load i32, i32* %pos_slot, align 4, !dbg !2088
  %and = and i32 %18, 1, !dbg !2089
  %or = or i32 2, %and, !dbg !2090
  %19 = load i32, i32* %footer_bits, align 4, !dbg !2091
  %shl = shl i32 %or, %19, !dbg !2092
  store i32 %shl, i32* %base, align 4, !dbg !2087
  call void @llvm.dbg.declare(metadata i32* %pos_reduced, metadata !2093, metadata !514), !dbg !2094
  %20 = load i32, i32* %distance.addr, align 4, !dbg !2095
  %21 = load i32, i32* %base, align 4, !dbg !2096
  %sub8 = sub i32 %20, %21, !dbg !2097
  store i32 %sub8, i32* %pos_reduced, align 4, !dbg !2094
  %22 = load i32, i32* %pos_slot, align 4, !dbg !2098
  %cmp9 = icmp ult i32 %22, 14, !dbg !2100
  br i1 %cmp9, label %if.then10, label %if.else, !dbg !2101

if.then10:                                        ; preds = %if.then
  %23 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2102
  %rc11 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %23, i32 0, i32 0, !dbg !2104
  %24 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2105
  %pos_special = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %24, i32 0, i32 20, !dbg !2106
  %arraydecay12 = getelementptr inbounds [114 x i16], [114 x i16]* %pos_special, i32 0, i32 0, !dbg !2105
  %25 = load i32, i32* %base, align 4, !dbg !2107
  %idx.ext = zext i32 %25 to i64, !dbg !2108
  %add.ptr = getelementptr inbounds i16, i16* %arraydecay12, i64 %idx.ext, !dbg !2108
  %26 = load i32, i32* %pos_slot, align 4, !dbg !2109
  %idx.ext13 = zext i32 %26 to i64, !dbg !2110
  %idx.neg = sub i64 0, %idx.ext13, !dbg !2110
  %add.ptr14 = getelementptr inbounds i16, i16* %add.ptr, i64 %idx.neg, !dbg !2110
  %add.ptr15 = getelementptr inbounds i16, i16* %add.ptr14, i64 -1, !dbg !2111
  %27 = load i32, i32* %footer_bits, align 4, !dbg !2112
  %28 = load i32, i32* %pos_reduced, align 4, !dbg !2113
  call void @rc_bittree_reverse(%struct.lzma_range_encoder* %rc11, i16* %add.ptr15, i32 %27, i32 %28), !dbg !2114
  br label %if.end, !dbg !2115

if.else:                                          ; preds = %if.then
  %29 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2116
  %rc16 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %29, i32 0, i32 0, !dbg !2118
  %30 = load i32, i32* %pos_reduced, align 4, !dbg !2119
  %shr17 = lshr i32 %30, 4, !dbg !2120
  %31 = load i32, i32* %footer_bits, align 4, !dbg !2121
  %sub18 = sub i32 %31, 4, !dbg !2122
  call void @rc_direct(%struct.lzma_range_encoder* %rc16, i32 %shr17, i32 %sub18), !dbg !2123
  %32 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2124
  %rc19 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %32, i32 0, i32 0, !dbg !2125
  %33 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2126
  %pos_align = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %33, i32 0, i32 21, !dbg !2127
  %arraydecay20 = getelementptr inbounds [16 x i16], [16 x i16]* %pos_align, i32 0, i32 0, !dbg !2126
  %34 = load i32, i32* %pos_reduced, align 4, !dbg !2128
  %and21 = and i32 %34, 15, !dbg !2129
  call void @rc_bittree_reverse(%struct.lzma_range_encoder* %rc19, i16* %arraydecay20, i32 4, i32 %and21), !dbg !2130
  %35 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2131
  %align_price_count = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %35, i32 0, i32 29, !dbg !2132
  %36 = load i32, i32* %align_price_count, align 8, !dbg !2133
  %inc = add i32 %36, 1, !dbg !2133
  store i32 %inc, i32* %align_price_count, align 8, !dbg !2133
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then10
  br label %if.end22, !dbg !2134

if.end22:                                         ; preds = %if.end, %cond.end
  %37 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2135
  %reps = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %37, i32 0, i32 2, !dbg !2136
  %arrayidx23 = getelementptr inbounds [4 x i32], [4 x i32]* %reps, i64 0, i64 2, !dbg !2135
  %38 = load i32, i32* %arrayidx23, align 4, !dbg !2135
  %39 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2137
  %reps24 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %39, i32 0, i32 2, !dbg !2138
  %arrayidx25 = getelementptr inbounds [4 x i32], [4 x i32]* %reps24, i64 0, i64 3, !dbg !2137
  store i32 %38, i32* %arrayidx25, align 4, !dbg !2139
  %40 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2140
  %reps26 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %40, i32 0, i32 2, !dbg !2141
  %arrayidx27 = getelementptr inbounds [4 x i32], [4 x i32]* %reps26, i64 0, i64 1, !dbg !2140
  %41 = load i32, i32* %arrayidx27, align 4, !dbg !2140
  %42 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2142
  %reps28 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %42, i32 0, i32 2, !dbg !2143
  %arrayidx29 = getelementptr inbounds [4 x i32], [4 x i32]* %reps28, i64 0, i64 2, !dbg !2142
  store i32 %41, i32* %arrayidx29, align 4, !dbg !2144
  %43 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2145
  %reps30 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %43, i32 0, i32 2, !dbg !2146
  %arrayidx31 = getelementptr inbounds [4 x i32], [4 x i32]* %reps30, i64 0, i64 0, !dbg !2145
  %44 = load i32, i32* %arrayidx31, align 4, !dbg !2145
  %45 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2147
  %reps32 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %45, i32 0, i32 2, !dbg !2148
  %arrayidx33 = getelementptr inbounds [4 x i32], [4 x i32]* %reps32, i64 0, i64 1, !dbg !2147
  store i32 %44, i32* %arrayidx33, align 4, !dbg !2149
  %46 = load i32, i32* %distance.addr, align 4, !dbg !2150
  %47 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2151
  %reps34 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %47, i32 0, i32 2, !dbg !2152
  %arrayidx35 = getelementptr inbounds [4 x i32], [4 x i32]* %reps34, i64 0, i64 0, !dbg !2151
  store i32 %46, i32* %arrayidx35, align 4, !dbg !2153
  %48 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2154
  %match_price_count = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %48, i32 0, i32 27, !dbg !2155
  %49 = load i32, i32* %match_price_count, align 4, !dbg !2156
  %inc36 = add i32 %49, 1, !dbg !2156
  store i32 %inc36, i32* %match_price_count, align 4, !dbg !2156
  ret void, !dbg !2157
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @literal_matched(%struct.lzma_range_encoder* %rc, i16* %subcoder, i32 %match_byte, i32 %symbol) #2 !dbg !429 {
entry:
  %rc.addr = alloca %struct.lzma_range_encoder*, align 8
  %subcoder.addr = alloca i16*, align 8
  %match_byte.addr = alloca i32, align 4
  %symbol.addr = alloca i32, align 4
  %offset = alloca i32, align 4
  %match_bit = alloca i32, align 4
  %subcoder_index = alloca i32, align 4
  %bit = alloca i32, align 4
  store %struct.lzma_range_encoder* %rc, %struct.lzma_range_encoder** %rc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_range_encoder** %rc.addr, metadata !2158, metadata !514), !dbg !2159
  store i16* %subcoder, i16** %subcoder.addr, align 8
  call void @llvm.dbg.declare(metadata i16** %subcoder.addr, metadata !2160, metadata !514), !dbg !2161
  store i32 %match_byte, i32* %match_byte.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %match_byte.addr, metadata !2162, metadata !514), !dbg !2163
  store i32 %symbol, i32* %symbol.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %symbol.addr, metadata !2164, metadata !514), !dbg !2165
  call void @llvm.dbg.declare(metadata i32* %offset, metadata !2166, metadata !514), !dbg !2167
  store i32 256, i32* %offset, align 4, !dbg !2167
  %0 = load i32, i32* %symbol.addr, align 4, !dbg !2168
  %add = add i32 %0, 256, !dbg !2168
  store i32 %add, i32* %symbol.addr, align 4, !dbg !2168
  br label %do.body, !dbg !2169

do.body:                                          ; preds = %do.cond, %entry
  call void @llvm.dbg.declare(metadata i32* %match_bit, metadata !2170, metadata !514), !dbg !2172
  call void @llvm.dbg.declare(metadata i32* %subcoder_index, metadata !2173, metadata !514), !dbg !2174
  call void @llvm.dbg.declare(metadata i32* %bit, metadata !2175, metadata !514), !dbg !2176
  %1 = load i32, i32* %match_byte.addr, align 4, !dbg !2177
  %shl = shl i32 %1, 1, !dbg !2177
  store i32 %shl, i32* %match_byte.addr, align 4, !dbg !2177
  %2 = load i32, i32* %match_byte.addr, align 4, !dbg !2178
  %3 = load i32, i32* %offset, align 4, !dbg !2179
  %and = and i32 %2, %3, !dbg !2180
  store i32 %and, i32* %match_bit, align 4, !dbg !2181
  %4 = load i32, i32* %offset, align 4, !dbg !2182
  %5 = load i32, i32* %match_bit, align 4, !dbg !2183
  %add1 = add i32 %4, %5, !dbg !2184
  %6 = load i32, i32* %symbol.addr, align 4, !dbg !2185
  %shr = lshr i32 %6, 8, !dbg !2186
  %add2 = add i32 %add1, %shr, !dbg !2187
  store i32 %add2, i32* %subcoder_index, align 4, !dbg !2188
  %7 = load i32, i32* %symbol.addr, align 4, !dbg !2189
  %shr3 = lshr i32 %7, 7, !dbg !2190
  %and4 = and i32 %shr3, 1, !dbg !2191
  store i32 %and4, i32* %bit, align 4, !dbg !2192
  %8 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !2193
  %9 = load i32, i32* %subcoder_index, align 4, !dbg !2194
  %idxprom = zext i32 %9 to i64, !dbg !2195
  %10 = load i16*, i16** %subcoder.addr, align 8, !dbg !2195
  %arrayidx = getelementptr inbounds i16, i16* %10, i64 %idxprom, !dbg !2195
  %11 = load i32, i32* %bit, align 4, !dbg !2196
  call void @rc_bit(%struct.lzma_range_encoder* %8, i16* %arrayidx, i32 %11), !dbg !2197
  %12 = load i32, i32* %symbol.addr, align 4, !dbg !2198
  %shl5 = shl i32 %12, 1, !dbg !2198
  store i32 %shl5, i32* %symbol.addr, align 4, !dbg !2198
  %13 = load i32, i32* %match_byte.addr, align 4, !dbg !2199
  %14 = load i32, i32* %symbol.addr, align 4, !dbg !2200
  %xor = xor i32 %13, %14, !dbg !2201
  %neg = xor i32 %xor, -1, !dbg !2202
  %15 = load i32, i32* %offset, align 4, !dbg !2203
  %and6 = and i32 %15, %neg, !dbg !2203
  store i32 %and6, i32* %offset, align 4, !dbg !2203
  br label %do.cond, !dbg !2204

do.cond:                                          ; preds = %do.body
  %16 = load i32, i32* %symbol.addr, align 4, !dbg !2205
  %cmp = icmp ult i32 %16, 65536, !dbg !2207
  br i1 %cmp, label %do.body, label %do.end, !dbg !2208

do.end:                                           ; preds = %do.cond
  ret void, !dbg !2209
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @length(%struct.lzma_range_encoder* %rc, %struct.lzma_length_encoder* %lc, i32 %pos_state, i32 %len, i1 zeroext %fast_mode) #2 !dbg !434 {
entry:
  %rc.addr = alloca %struct.lzma_range_encoder*, align 8
  %lc.addr = alloca %struct.lzma_length_encoder*, align 8
  %pos_state.addr = alloca i32, align 4
  %len.addr = alloca i32, align 4
  %fast_mode.addr = alloca i8, align 1
  store %struct.lzma_range_encoder* %rc, %struct.lzma_range_encoder** %rc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_range_encoder** %rc.addr, metadata !2210, metadata !514), !dbg !2211
  store %struct.lzma_length_encoder* %lc, %struct.lzma_length_encoder** %lc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_length_encoder** %lc.addr, metadata !2212, metadata !514), !dbg !2213
  store i32 %pos_state, i32* %pos_state.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %pos_state.addr, metadata !2214, metadata !514), !dbg !2215
  store i32 %len, i32* %len.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len.addr, metadata !2216, metadata !514), !dbg !2217
  %frombool = zext i1 %fast_mode to i8
  store i8 %frombool, i8* %fast_mode.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %fast_mode.addr, metadata !2218, metadata !514), !dbg !2219
  %0 = load i32, i32* %len.addr, align 4, !dbg !2220
  %cmp = icmp ule i32 %0, 273, !dbg !2220
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !2220

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !2221

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([50 x i8], [50 x i8]* @.str.11, i32 0, i32 0), i8* getelementptr inbounds ([82 x i8], [82 x i8]* @.str.1, i32 0, i32 0), i32 116, i8* getelementptr inbounds ([96 x i8], [96 x i8]* @__PRETTY_FUNCTION__.length, i32 0, i32 0)) #6, !dbg !2223
  unreachable, !dbg !2223
                                                  ; No predecessors!
  br label %cond.end, !dbg !2225

cond.end:                                         ; preds = %1, %cond.true
  %2 = load i32, i32* %len.addr, align 4, !dbg !2227
  %sub = sub i32 %2, 2, !dbg !2227
  store i32 %sub, i32* %len.addr, align 4, !dbg !2227
  %3 = load i32, i32* %len.addr, align 4, !dbg !2228
  %cmp1 = icmp ult i32 %3, 8, !dbg !2230
  br i1 %cmp1, label %if.then, label %if.else, !dbg !2231

if.then:                                          ; preds = %cond.end
  %4 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !2232
  %5 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lc.addr, align 8, !dbg !2234
  %choice = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %5, i32 0, i32 0, !dbg !2235
  call void @rc_bit(%struct.lzma_range_encoder* %4, i16* %choice, i32 0), !dbg !2236
  %6 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !2237
  %7 = load i32, i32* %pos_state.addr, align 4, !dbg !2238
  %idxprom = zext i32 %7 to i64, !dbg !2239
  %8 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lc.addr, align 8, !dbg !2239
  %low = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %8, i32 0, i32 2, !dbg !2240
  %arrayidx = getelementptr inbounds [16 x [8 x i16]], [16 x [8 x i16]]* %low, i64 0, i64 %idxprom, !dbg !2239
  %arraydecay = getelementptr inbounds [8 x i16], [8 x i16]* %arrayidx, i32 0, i32 0, !dbg !2239
  %9 = load i32, i32* %len.addr, align 4, !dbg !2241
  call void @rc_bittree(%struct.lzma_range_encoder* %6, i16* %arraydecay, i32 3, i32 %9), !dbg !2242
  br label %if.end14, !dbg !2243

if.else:                                          ; preds = %cond.end
  %10 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !2244
  %11 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lc.addr, align 8, !dbg !2246
  %choice2 = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %11, i32 0, i32 0, !dbg !2247
  call void @rc_bit(%struct.lzma_range_encoder* %10, i16* %choice2, i32 1), !dbg !2248
  %12 = load i32, i32* %len.addr, align 4, !dbg !2249
  %sub3 = sub i32 %12, 8, !dbg !2249
  store i32 %sub3, i32* %len.addr, align 4, !dbg !2249
  %13 = load i32, i32* %len.addr, align 4, !dbg !2250
  %cmp4 = icmp ult i32 %13, 8, !dbg !2252
  br i1 %cmp4, label %if.then5, label %if.else10, !dbg !2253

if.then5:                                         ; preds = %if.else
  %14 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !2254
  %15 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lc.addr, align 8, !dbg !2256
  %choice26 = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %15, i32 0, i32 1, !dbg !2257
  call void @rc_bit(%struct.lzma_range_encoder* %14, i16* %choice26, i32 0), !dbg !2258
  %16 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !2259
  %17 = load i32, i32* %pos_state.addr, align 4, !dbg !2260
  %idxprom7 = zext i32 %17 to i64, !dbg !2261
  %18 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lc.addr, align 8, !dbg !2261
  %mid = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %18, i32 0, i32 3, !dbg !2262
  %arrayidx8 = getelementptr inbounds [16 x [8 x i16]], [16 x [8 x i16]]* %mid, i64 0, i64 %idxprom7, !dbg !2261
  %arraydecay9 = getelementptr inbounds [8 x i16], [8 x i16]* %arrayidx8, i32 0, i32 0, !dbg !2261
  %19 = load i32, i32* %len.addr, align 4, !dbg !2263
  call void @rc_bittree(%struct.lzma_range_encoder* %16, i16* %arraydecay9, i32 3, i32 %19), !dbg !2264
  br label %if.end, !dbg !2265

if.else10:                                        ; preds = %if.else
  %20 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !2266
  %21 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lc.addr, align 8, !dbg !2268
  %choice211 = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %21, i32 0, i32 1, !dbg !2269
  call void @rc_bit(%struct.lzma_range_encoder* %20, i16* %choice211, i32 1), !dbg !2270
  %22 = load i32, i32* %len.addr, align 4, !dbg !2271
  %sub12 = sub i32 %22, 8, !dbg !2271
  store i32 %sub12, i32* %len.addr, align 4, !dbg !2271
  %23 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !2272
  %24 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lc.addr, align 8, !dbg !2273
  %high = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %24, i32 0, i32 4, !dbg !2274
  %arraydecay13 = getelementptr inbounds [256 x i16], [256 x i16]* %high, i32 0, i32 0, !dbg !2273
  %25 = load i32, i32* %len.addr, align 4, !dbg !2275
  call void @rc_bittree(%struct.lzma_range_encoder* %23, i16* %arraydecay13, i32 8, i32 %25), !dbg !2276
  br label %if.end

if.end:                                           ; preds = %if.else10, %if.then5
  br label %if.end14

if.end14:                                         ; preds = %if.end, %if.then
  %26 = load i8, i8* %fast_mode.addr, align 1, !dbg !2277
  %tobool = trunc i8 %26 to i1, !dbg !2277
  br i1 %tobool, label %if.end21, label %if.then15, !dbg !2279

if.then15:                                        ; preds = %if.end14
  %27 = load i32, i32* %pos_state.addr, align 4, !dbg !2280
  %idxprom16 = zext i32 %27 to i64, !dbg !2282
  %28 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lc.addr, align 8, !dbg !2282
  %counters = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %28, i32 0, i32 7, !dbg !2283
  %arrayidx17 = getelementptr inbounds [16 x i32], [16 x i32]* %counters, i64 0, i64 %idxprom16, !dbg !2282
  %29 = load i32, i32* %arrayidx17, align 4, !dbg !2284
  %dec = add i32 %29, -1, !dbg !2284
  store i32 %dec, i32* %arrayidx17, align 4, !dbg !2284
  %cmp18 = icmp eq i32 %dec, 0, !dbg !2285
  br i1 %cmp18, label %if.then19, label %if.end20, !dbg !2286

if.then19:                                        ; preds = %if.then15
  %30 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lc.addr, align 8, !dbg !2287
  %31 = load i32, i32* %pos_state.addr, align 4, !dbg !2288
  call void @length_update_prices(%struct.lzma_length_encoder* %30, i32 %31), !dbg !2289
  br label %if.end20, !dbg !2289

if.end20:                                         ; preds = %if.then19, %if.then15
  br label %if.end21, !dbg !2290

if.end21:                                         ; preds = %if.end20, %if.end14
  ret void, !dbg !2292
}

; Function Attrs: nounwind uwtable
define internal void @length_update_prices(%struct.lzma_length_encoder* %lc, i32 %pos_state) #0 !dbg !439 {
entry:
  %lc.addr = alloca %struct.lzma_length_encoder*, align 8
  %pos_state.addr = alloca i32, align 4
  %a0 = alloca i32, align 4
  %a1 = alloca i32, align 4
  %b0 = alloca i32, align 4
  %b1 = alloca i32, align 4
  %prices = alloca i32*, align 8
  %i = alloca i32, align 4
  %table_size = alloca i32, align 4
  store %struct.lzma_length_encoder* %lc, %struct.lzma_length_encoder** %lc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_length_encoder** %lc.addr, metadata !2293, metadata !514), !dbg !2294
  store i32 %pos_state, i32* %pos_state.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %pos_state.addr, metadata !2295, metadata !514), !dbg !2296
  call void @llvm.dbg.declare(metadata i32* %a0, metadata !2297, metadata !514), !dbg !2298
  call void @llvm.dbg.declare(metadata i32* %a1, metadata !2299, metadata !514), !dbg !2300
  call void @llvm.dbg.declare(metadata i32* %b0, metadata !2301, metadata !514), !dbg !2302
  call void @llvm.dbg.declare(metadata i32* %b1, metadata !2303, metadata !514), !dbg !2304
  call void @llvm.dbg.declare(metadata i32** %prices, metadata !2305, metadata !514), !dbg !2306
  call void @llvm.dbg.declare(metadata i32* %i, metadata !2307, metadata !514), !dbg !2308
  call void @llvm.dbg.declare(metadata i32* %table_size, metadata !2309, metadata !514), !dbg !2310
  %0 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lc.addr, align 8, !dbg !2311
  %table_size1 = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %0, i32 0, i32 6, !dbg !2312
  %1 = load i32, i32* %table_size1, align 4, !dbg !2312
  store i32 %1, i32* %table_size, align 4, !dbg !2310
  %2 = load i32, i32* %table_size, align 4, !dbg !2313
  %3 = load i32, i32* %pos_state.addr, align 4, !dbg !2314
  %idxprom = zext i32 %3 to i64, !dbg !2315
  %4 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lc.addr, align 8, !dbg !2315
  %counters = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %4, i32 0, i32 7, !dbg !2316
  %arrayidx = getelementptr inbounds [16 x i32], [16 x i32]* %counters, i64 0, i64 %idxprom, !dbg !2315
  store i32 %2, i32* %arrayidx, align 4, !dbg !2317
  %5 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lc.addr, align 8, !dbg !2318
  %choice = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %5, i32 0, i32 0, !dbg !2319
  %6 = load i16, i16* %choice, align 4, !dbg !2319
  %call = call i32 @rc_bit_0_price(i16 zeroext %6), !dbg !2320
  store i32 %call, i32* %a0, align 4, !dbg !2321
  %7 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lc.addr, align 8, !dbg !2322
  %choice2 = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %7, i32 0, i32 0, !dbg !2323
  %8 = load i16, i16* %choice2, align 4, !dbg !2323
  %call3 = call i32 @rc_bit_1_price(i16 zeroext %8), !dbg !2324
  store i32 %call3, i32* %a1, align 4, !dbg !2325
  %9 = load i32, i32* %a1, align 4, !dbg !2326
  %10 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lc.addr, align 8, !dbg !2327
  %choice24 = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %10, i32 0, i32 1, !dbg !2328
  %11 = load i16, i16* %choice24, align 2, !dbg !2328
  %call5 = call i32 @rc_bit_0_price(i16 zeroext %11), !dbg !2329
  %add = add i32 %9, %call5, !dbg !2330
  store i32 %add, i32* %b0, align 4, !dbg !2331
  %12 = load i32, i32* %a1, align 4, !dbg !2332
  %13 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lc.addr, align 8, !dbg !2333
  %choice26 = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %13, i32 0, i32 1, !dbg !2334
  %14 = load i16, i16* %choice26, align 2, !dbg !2334
  %call7 = call i32 @rc_bit_1_price(i16 zeroext %14), !dbg !2335
  %add8 = add i32 %12, %call7, !dbg !2336
  store i32 %add8, i32* %b1, align 4, !dbg !2337
  %15 = load i32, i32* %pos_state.addr, align 4, !dbg !2338
  %idxprom9 = zext i32 %15 to i64, !dbg !2339
  %16 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lc.addr, align 8, !dbg !2339
  %prices10 = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %16, i32 0, i32 5, !dbg !2340
  %arrayidx11 = getelementptr inbounds [16 x [272 x i32]], [16 x [272 x i32]]* %prices10, i64 0, i64 %idxprom9, !dbg !2339
  %arraydecay = getelementptr inbounds [272 x i32], [272 x i32]* %arrayidx11, i32 0, i32 0, !dbg !2339
  store i32* %arraydecay, i32** %prices, align 8, !dbg !2341
  store i32 0, i32* %i, align 4, !dbg !2342
  br label %for.cond, !dbg !2344

for.cond:                                         ; preds = %for.inc, %entry
  %17 = load i32, i32* %i, align 4, !dbg !2345
  %18 = load i32, i32* %table_size, align 4, !dbg !2348
  %cmp = icmp ult i32 %17, %18, !dbg !2349
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !2350

land.rhs:                                         ; preds = %for.cond
  %19 = load i32, i32* %i, align 4, !dbg !2351
  %cmp12 = icmp ult i32 %19, 8, !dbg !2353
  br label %land.end

land.end:                                         ; preds = %land.rhs, %for.cond
  %20 = phi i1 [ false, %for.cond ], [ %cmp12, %land.rhs ]
  br i1 %20, label %for.body, label %for.end, !dbg !2354

for.body:                                         ; preds = %land.end
  %21 = load i32, i32* %a0, align 4, !dbg !2356
  %22 = load i32, i32* %pos_state.addr, align 4, !dbg !2357
  %idxprom13 = zext i32 %22 to i64, !dbg !2358
  %23 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lc.addr, align 8, !dbg !2358
  %low = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %23, i32 0, i32 2, !dbg !2359
  %arrayidx14 = getelementptr inbounds [16 x [8 x i16]], [16 x [8 x i16]]* %low, i64 0, i64 %idxprom13, !dbg !2358
  %arraydecay15 = getelementptr inbounds [8 x i16], [8 x i16]* %arrayidx14, i32 0, i32 0, !dbg !2358
  %24 = load i32, i32* %i, align 4, !dbg !2360
  %call16 = call i32 @rc_bittree_price(i16* %arraydecay15, i32 3, i32 %24), !dbg !2361
  %add17 = add i32 %21, %call16, !dbg !2362
  %25 = load i32, i32* %i, align 4, !dbg !2363
  %idxprom18 = zext i32 %25 to i64, !dbg !2364
  %26 = load i32*, i32** %prices, align 8, !dbg !2364
  %arrayidx19 = getelementptr inbounds i32, i32* %26, i64 %idxprom18, !dbg !2364
  store i32 %add17, i32* %arrayidx19, align 4, !dbg !2365
  br label %for.inc, !dbg !2364

for.inc:                                          ; preds = %for.body
  %27 = load i32, i32* %i, align 4, !dbg !2366
  %inc = add i32 %27, 1, !dbg !2366
  store i32 %inc, i32* %i, align 4, !dbg !2366
  br label %for.cond, !dbg !2368

for.end:                                          ; preds = %land.end
  br label %for.cond20, !dbg !2369

for.cond20:                                       ; preds = %for.inc33, %for.end
  %28 = load i32, i32* %i, align 4, !dbg !2370
  %29 = load i32, i32* %table_size, align 4, !dbg !2374
  %cmp21 = icmp ult i32 %28, %29, !dbg !2375
  br i1 %cmp21, label %land.rhs22, label %land.end24, !dbg !2376

land.rhs22:                                       ; preds = %for.cond20
  %30 = load i32, i32* %i, align 4, !dbg !2377
  %cmp23 = icmp ult i32 %30, 16, !dbg !2379
  br label %land.end24

land.end24:                                       ; preds = %land.rhs22, %for.cond20
  %31 = phi i1 [ false, %for.cond20 ], [ %cmp23, %land.rhs22 ]
  br i1 %31, label %for.body25, label %for.end35, !dbg !2380

for.body25:                                       ; preds = %land.end24
  %32 = load i32, i32* %b0, align 4, !dbg !2382
  %33 = load i32, i32* %pos_state.addr, align 4, !dbg !2383
  %idxprom26 = zext i32 %33 to i64, !dbg !2384
  %34 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lc.addr, align 8, !dbg !2384
  %mid = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %34, i32 0, i32 3, !dbg !2385
  %arrayidx27 = getelementptr inbounds [16 x [8 x i16]], [16 x [8 x i16]]* %mid, i64 0, i64 %idxprom26, !dbg !2384
  %arraydecay28 = getelementptr inbounds [8 x i16], [8 x i16]* %arrayidx27, i32 0, i32 0, !dbg !2384
  %35 = load i32, i32* %i, align 4, !dbg !2386
  %sub = sub i32 %35, 8, !dbg !2387
  %call29 = call i32 @rc_bittree_price(i16* %arraydecay28, i32 3, i32 %sub), !dbg !2388
  %add30 = add i32 %32, %call29, !dbg !2389
  %36 = load i32, i32* %i, align 4, !dbg !2390
  %idxprom31 = zext i32 %36 to i64, !dbg !2391
  %37 = load i32*, i32** %prices, align 8, !dbg !2391
  %arrayidx32 = getelementptr inbounds i32, i32* %37, i64 %idxprom31, !dbg !2391
  store i32 %add30, i32* %arrayidx32, align 4, !dbg !2392
  br label %for.inc33, !dbg !2391

for.inc33:                                        ; preds = %for.body25
  %38 = load i32, i32* %i, align 4, !dbg !2393
  %inc34 = add i32 %38, 1, !dbg !2393
  store i32 %inc34, i32* %i, align 4, !dbg !2393
  br label %for.cond20, !dbg !2395

for.end35:                                        ; preds = %land.end24
  br label %for.cond36, !dbg !2396

for.cond36:                                       ; preds = %for.inc46, %for.end35
  %39 = load i32, i32* %i, align 4, !dbg !2397
  %40 = load i32, i32* %table_size, align 4, !dbg !2401
  %cmp37 = icmp ult i32 %39, %40, !dbg !2402
  br i1 %cmp37, label %for.body38, label %for.end48, !dbg !2403

for.body38:                                       ; preds = %for.cond36
  %41 = load i32, i32* %b1, align 4, !dbg !2404
  %42 = load %struct.lzma_length_encoder*, %struct.lzma_length_encoder** %lc.addr, align 8, !dbg !2405
  %high = getelementptr inbounds %struct.lzma_length_encoder, %struct.lzma_length_encoder* %42, i32 0, i32 4, !dbg !2406
  %arraydecay39 = getelementptr inbounds [256 x i16], [256 x i16]* %high, i32 0, i32 0, !dbg !2405
  %43 = load i32, i32* %i, align 4, !dbg !2407
  %sub40 = sub i32 %43, 8, !dbg !2408
  %sub41 = sub i32 %sub40, 8, !dbg !2409
  %call42 = call i32 @rc_bittree_price(i16* %arraydecay39, i32 8, i32 %sub41), !dbg !2410
  %add43 = add i32 %41, %call42, !dbg !2411
  %44 = load i32, i32* %i, align 4, !dbg !2412
  %idxprom44 = zext i32 %44 to i64, !dbg !2413
  %45 = load i32*, i32** %prices, align 8, !dbg !2413
  %arrayidx45 = getelementptr inbounds i32, i32* %45, i64 %idxprom44, !dbg !2413
  store i32 %add43, i32* %arrayidx45, align 4, !dbg !2414
  br label %for.inc46, !dbg !2413

for.inc46:                                        ; preds = %for.body38
  %46 = load i32, i32* %i, align 4, !dbg !2415
  %inc47 = add i32 %46, 1, !dbg !2415
  store i32 %inc47, i32* %i, align 4, !dbg !2415
  br label %for.cond36, !dbg !2417

for.end48:                                        ; preds = %for.cond36
  ret void, !dbg !2418
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @rc_bit_0_price(i16 zeroext %prob) #2 !dbg !442 {
entry:
  %prob.addr = alloca i16, align 2
  store i16 %prob, i16* %prob.addr, align 2
  call void @llvm.dbg.declare(metadata i16* %prob.addr, metadata !2419, metadata !514), !dbg !2420
  %0 = load i16, i16* %prob.addr, align 2, !dbg !2421
  %conv = zext i16 %0 to i32, !dbg !2421
  %shr = ashr i32 %conv, 4, !dbg !2422
  %idxprom = sext i32 %shr to i64, !dbg !2423
  %arrayidx = getelementptr inbounds [128 x i8], [128 x i8]* @lzma_rc_prices, i64 0, i64 %idxprom, !dbg !2423
  %1 = load i8, i8* %arrayidx, align 1, !dbg !2423
  %conv1 = zext i8 %1 to i32, !dbg !2423
  ret i32 %conv1, !dbg !2424
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @rc_bit_1_price(i16 zeroext %prob) #2 !dbg !447 {
entry:
  %prob.addr = alloca i16, align 2
  store i16 %prob, i16* %prob.addr, align 2
  call void @llvm.dbg.declare(metadata i16* %prob.addr, metadata !2425, metadata !514), !dbg !2426
  %0 = load i16, i16* %prob.addr, align 2, !dbg !2427
  %conv = zext i16 %0 to i32, !dbg !2427
  %xor = xor i32 %conv, 2047, !dbg !2428
  %shr = lshr i32 %xor, 4, !dbg !2429
  %idxprom = zext i32 %shr to i64, !dbg !2430
  %arrayidx = getelementptr inbounds [128 x i8], [128 x i8]* @lzma_rc_prices, i64 0, i64 %idxprom, !dbg !2430
  %1 = load i8, i8* %arrayidx, align 1, !dbg !2430
  %conv1 = zext i8 %1 to i32, !dbg !2430
  ret i32 %conv1, !dbg !2431
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @rc_bittree_price(i16* %probs, i32 %bit_levels, i32 %symbol) #2 !dbg !448 {
entry:
  %probs.addr = alloca i16*, align 8
  %bit_levels.addr = alloca i32, align 4
  %symbol.addr = alloca i32, align 4
  %price = alloca i32, align 4
  %bit = alloca i32, align 4
  store i16* %probs, i16** %probs.addr, align 8
  call void @llvm.dbg.declare(metadata i16** %probs.addr, metadata !2432, metadata !514), !dbg !2433
  store i32 %bit_levels, i32* %bit_levels.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %bit_levels.addr, metadata !2434, metadata !514), !dbg !2435
  store i32 %symbol, i32* %symbol.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %symbol.addr, metadata !2436, metadata !514), !dbg !2437
  call void @llvm.dbg.declare(metadata i32* %price, metadata !2438, metadata !514), !dbg !2439
  store i32 0, i32* %price, align 4, !dbg !2439
  %0 = load i32, i32* %bit_levels.addr, align 4, !dbg !2440
  %shl = shl i32 1, %0, !dbg !2441
  %1 = load i32, i32* %symbol.addr, align 4, !dbg !2442
  %add = add i32 %1, %shl, !dbg !2442
  store i32 %add, i32* %symbol.addr, align 4, !dbg !2442
  br label %do.body, !dbg !2443

do.body:                                          ; preds = %do.cond, %entry
  call void @llvm.dbg.declare(metadata i32* %bit, metadata !2444, metadata !514), !dbg !2446
  %2 = load i32, i32* %symbol.addr, align 4, !dbg !2447
  %and = and i32 %2, 1, !dbg !2448
  store i32 %and, i32* %bit, align 4, !dbg !2446
  %3 = load i32, i32* %symbol.addr, align 4, !dbg !2449
  %shr = lshr i32 %3, 1, !dbg !2449
  store i32 %shr, i32* %symbol.addr, align 4, !dbg !2449
  %4 = load i32, i32* %symbol.addr, align 4, !dbg !2450
  %idxprom = zext i32 %4 to i64, !dbg !2451
  %5 = load i16*, i16** %probs.addr, align 8, !dbg !2451
  %arrayidx = getelementptr inbounds i16, i16* %5, i64 %idxprom, !dbg !2451
  %6 = load i16, i16* %arrayidx, align 2, !dbg !2451
  %7 = load i32, i32* %bit, align 4, !dbg !2452
  %call = call i32 @rc_bit_price(i16 zeroext %6, i32 %7), !dbg !2453
  %8 = load i32, i32* %price, align 4, !dbg !2454
  %add1 = add i32 %8, %call, !dbg !2454
  store i32 %add1, i32* %price, align 4, !dbg !2454
  br label %do.cond, !dbg !2455

do.cond:                                          ; preds = %do.body
  %9 = load i32, i32* %symbol.addr, align 4, !dbg !2456
  %cmp = icmp ne i32 %9, 1, !dbg !2458
  br i1 %cmp, label %do.body, label %do.end, !dbg !2459

do.end:                                           ; preds = %do.cond
  %10 = load i32, i32* %price, align 4, !dbg !2460
  ret i32 %10, !dbg !2461
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @rc_bit_price(i16 zeroext %prob, i32 %bit) #2 !dbg !453 {
entry:
  %prob.addr = alloca i16, align 2
  %bit.addr = alloca i32, align 4
  store i16 %prob, i16* %prob.addr, align 2
  call void @llvm.dbg.declare(metadata i16* %prob.addr, metadata !2462, metadata !514), !dbg !2463
  store i32 %bit, i32* %bit.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %bit.addr, metadata !2464, metadata !514), !dbg !2465
  %0 = load i16, i16* %prob.addr, align 2, !dbg !2466
  %conv = zext i16 %0 to i32, !dbg !2466
  %1 = load i32, i32* %bit.addr, align 4, !dbg !2467
  %sub = sub i32 0, %1, !dbg !2468
  %and = and i32 %sub, 2047, !dbg !2469
  %xor = xor i32 %conv, %and, !dbg !2470
  %shr = lshr i32 %xor, 4, !dbg !2471
  %idxprom = zext i32 %shr to i64, !dbg !2472
  %arrayidx = getelementptr inbounds [128 x i8], [128 x i8]* @lzma_rc_prices, i64 0, i64 %idxprom, !dbg !2472
  %2 = load i8, i8* %arrayidx, align 1, !dbg !2472
  %conv1 = zext i8 %2 to i32, !dbg !2472
  ret i32 %conv1, !dbg !2473
}

; Function Attrs: inlinehint nounwind uwtable
define internal i32 @get_pos_slot(i32 %pos) #2 !dbg !457 {
entry:
  %retval = alloca i32, align 4
  %pos.addr = alloca i32, align 4
  store i32 %pos, i32* %pos.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %pos.addr, metadata !2474, metadata !514), !dbg !2475
  %0 = load i32, i32* %pos.addr, align 4, !dbg !2476
  %cmp = icmp ult i32 %0, 8192, !dbg !2478
  br i1 %cmp, label %if.then, label %if.end, !dbg !2479

if.then:                                          ; preds = %entry
  %1 = load i32, i32* %pos.addr, align 4, !dbg !2480
  %idxprom = zext i32 %1 to i64, !dbg !2481
  %arrayidx = getelementptr inbounds [8192 x i8], [8192 x i8]* @lzma_fastpos, i64 0, i64 %idxprom, !dbg !2481
  %2 = load i8, i8* %arrayidx, align 1, !dbg !2481
  %conv = zext i8 %2 to i32, !dbg !2481
  store i32 %conv, i32* %retval, align 4, !dbg !2482
  br label %return, !dbg !2482

if.end:                                           ; preds = %entry
  %3 = load i32, i32* %pos.addr, align 4, !dbg !2483
  %cmp1 = icmp ult i32 %3, 33554432, !dbg !2485
  br i1 %cmp1, label %if.then3, label %if.end7, !dbg !2486

if.then3:                                         ; preds = %if.end
  %4 = load i32, i32* %pos.addr, align 4, !dbg !2487
  %shr = lshr i32 %4, 12, !dbg !2487
  %idxprom4 = zext i32 %shr to i64, !dbg !2487
  %arrayidx5 = getelementptr inbounds [8192 x i8], [8192 x i8]* @lzma_fastpos, i64 0, i64 %idxprom4, !dbg !2487
  %5 = load i8, i8* %arrayidx5, align 1, !dbg !2487
  %conv6 = zext i8 %5 to i32, !dbg !2487
  %add = add nsw i32 %conv6, 24, !dbg !2487
  store i32 %add, i32* %retval, align 4, !dbg !2488
  br label %return, !dbg !2488

if.end7:                                          ; preds = %if.end
  %6 = load i32, i32* %pos.addr, align 4, !dbg !2489
  %shr8 = lshr i32 %6, 24, !dbg !2489
  %idxprom9 = zext i32 %shr8 to i64, !dbg !2489
  %arrayidx10 = getelementptr inbounds [8192 x i8], [8192 x i8]* @lzma_fastpos, i64 0, i64 %idxprom9, !dbg !2489
  %7 = load i8, i8* %arrayidx10, align 1, !dbg !2489
  %conv11 = zext i8 %7 to i32, !dbg !2489
  %add12 = add nsw i32 %conv11, 48, !dbg !2489
  store i32 %add12, i32* %retval, align 4, !dbg !2490
  br label %return, !dbg !2490

return:                                           ; preds = %if.end7, %if.then3, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !2491
  ret i32 %8, !dbg !2491
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @rc_bittree_reverse(%struct.lzma_range_encoder* %rc, i16* %probs, i32 %bit_count, i32 %symbol) #2 !dbg !461 {
entry:
  %rc.addr = alloca %struct.lzma_range_encoder*, align 8
  %probs.addr = alloca i16*, align 8
  %bit_count.addr = alloca i32, align 4
  %symbol.addr = alloca i32, align 4
  %model_index = alloca i32, align 4
  %bit = alloca i32, align 4
  store %struct.lzma_range_encoder* %rc, %struct.lzma_range_encoder** %rc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_range_encoder** %rc.addr, metadata !2492, metadata !514), !dbg !2493
  store i16* %probs, i16** %probs.addr, align 8
  call void @llvm.dbg.declare(metadata i16** %probs.addr, metadata !2494, metadata !514), !dbg !2495
  store i32 %bit_count, i32* %bit_count.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %bit_count.addr, metadata !2496, metadata !514), !dbg !2497
  store i32 %symbol, i32* %symbol.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %symbol.addr, metadata !2498, metadata !514), !dbg !2499
  call void @llvm.dbg.declare(metadata i32* %model_index, metadata !2500, metadata !514), !dbg !2501
  store i32 1, i32* %model_index, align 4, !dbg !2501
  br label %do.body, !dbg !2502

do.body:                                          ; preds = %do.cond, %entry
  call void @llvm.dbg.declare(metadata i32* %bit, metadata !2503, metadata !514), !dbg !2505
  %0 = load i32, i32* %symbol.addr, align 4, !dbg !2506
  %and = and i32 %0, 1, !dbg !2507
  store i32 %and, i32* %bit, align 4, !dbg !2505
  %1 = load i32, i32* %symbol.addr, align 4, !dbg !2508
  %shr = lshr i32 %1, 1, !dbg !2508
  store i32 %shr, i32* %symbol.addr, align 4, !dbg !2508
  %2 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !2509
  %3 = load i32, i32* %model_index, align 4, !dbg !2510
  %idxprom = zext i32 %3 to i64, !dbg !2511
  %4 = load i16*, i16** %probs.addr, align 8, !dbg !2511
  %arrayidx = getelementptr inbounds i16, i16* %4, i64 %idxprom, !dbg !2511
  %5 = load i32, i32* %bit, align 4, !dbg !2512
  call void @rc_bit(%struct.lzma_range_encoder* %2, i16* %arrayidx, i32 %5), !dbg !2513
  %6 = load i32, i32* %model_index, align 4, !dbg !2514
  %shl = shl i32 %6, 1, !dbg !2515
  %7 = load i32, i32* %bit, align 4, !dbg !2516
  %add = add i32 %shl, %7, !dbg !2517
  store i32 %add, i32* %model_index, align 4, !dbg !2518
  br label %do.cond, !dbg !2519

do.cond:                                          ; preds = %do.body
  %8 = load i32, i32* %bit_count.addr, align 4, !dbg !2520
  %dec = add i32 %8, -1, !dbg !2520
  store i32 %dec, i32* %bit_count.addr, align 4, !dbg !2520
  %cmp = icmp ne i32 %dec, 0, !dbg !2522
  br i1 %cmp, label %do.body, label %do.end, !dbg !2523

do.end:                                           ; preds = %do.cond
  ret void, !dbg !2524
}

; Function Attrs: inlinehint nounwind uwtable
define internal void @rc_direct(%struct.lzma_range_encoder* %rc, i32 %value, i32 %bit_count) #2 !dbg !462 {
entry:
  %rc.addr = alloca %struct.lzma_range_encoder*, align 8
  %value.addr = alloca i32, align 4
  %bit_count.addr = alloca i32, align 4
  store %struct.lzma_range_encoder* %rc, %struct.lzma_range_encoder** %rc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_range_encoder** %rc.addr, metadata !2525, metadata !514), !dbg !2526
  store i32 %value, i32* %value.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %value.addr, metadata !2527, metadata !514), !dbg !2528
  store i32 %bit_count, i32* %bit_count.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %bit_count.addr, metadata !2529, metadata !514), !dbg !2530
  br label %do.body, !dbg !2531

do.body:                                          ; preds = %do.cond, %entry
  %0 = load i32, i32* %value.addr, align 4, !dbg !2532
  %1 = load i32, i32* %bit_count.addr, align 4, !dbg !2534
  %dec = add i32 %1, -1, !dbg !2534
  store i32 %dec, i32* %bit_count.addr, align 4, !dbg !2534
  %shr = lshr i32 %0, %dec, !dbg !2535
  %and = and i32 %shr, 1, !dbg !2536
  %add = add i32 2, %and, !dbg !2537
  %2 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !2538
  %count = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %2, i32 0, i32 4, !dbg !2539
  %3 = load i64, i64* %count, align 8, !dbg !2540
  %inc = add i64 %3, 1, !dbg !2540
  store i64 %inc, i64* %count, align 8, !dbg !2540
  %4 = load %struct.lzma_range_encoder*, %struct.lzma_range_encoder** %rc.addr, align 8, !dbg !2541
  %symbols = getelementptr inbounds %struct.lzma_range_encoder, %struct.lzma_range_encoder* %4, i32 0, i32 6, !dbg !2542
  %arrayidx = getelementptr inbounds [58 x i32], [58 x i32]* %symbols, i64 0, i64 %3, !dbg !2541
  store i32 %add, i32* %arrayidx, align 4, !dbg !2543
  br label %do.cond, !dbg !2544

do.cond:                                          ; preds = %do.body
  %5 = load i32, i32* %bit_count.addr, align 4, !dbg !2545
  %cmp = icmp ne i32 %5, 0, !dbg !2547
  br i1 %cmp, label %do.body, label %do.end, !dbg !2548

do.end:                                           ; preds = %do.cond
  ret void, !dbg !2549
}

; Function Attrs: nounwind uwtable
define internal i32 @lzma_encode(%struct.lzma_coder_s* noalias %coder, %struct.lzma_mf_s* noalias %mf, i8* noalias %out, i64* noalias %out_pos, i64 %out_size) #0 !dbg !504 {
entry:
  %retval = alloca i32, align 4
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %mf.addr = alloca %struct.lzma_mf_s*, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !2550, metadata !514), !dbg !2551
  store %struct.lzma_mf_s* %mf, %struct.lzma_mf_s** %mf.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_mf_s** %mf.addr, metadata !2552, metadata !514), !dbg !2553
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !2554, metadata !514), !dbg !2555
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !2556, metadata !514), !dbg !2557
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !2558, metadata !514), !dbg !2559
  %0 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !2560
  %action = getelementptr inbounds %struct.lzma_mf_s, %struct.lzma_mf_s* %0, i32 0, i32 20, !dbg !2560
  %1 = load i32, i32* %action, align 8, !dbg !2560
  %cmp = icmp eq i32 %1, 1, !dbg !2560
  %conv = zext i1 %cmp to i32, !dbg !2560
  %conv1 = sext i32 %conv to i64, !dbg !2560
  %tobool = icmp ne i64 %conv1, 0, !dbg !2560
  br i1 %tobool, label %if.then, label %if.end, !dbg !2562

if.then:                                          ; preds = %entry
  store i32 8, i32* %retval, align 4, !dbg !2563
  br label %return, !dbg !2563

if.end:                                           ; preds = %entry
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !2564
  %3 = load %struct.lzma_mf_s*, %struct.lzma_mf_s** %mf.addr, align 8, !dbg !2565
  %4 = load i8*, i8** %out.addr, align 8, !dbg !2566
  %5 = load i64*, i64** %out_pos.addr, align 8, !dbg !2567
  %6 = load i64, i64* %out_size.addr, align 8, !dbg !2568
  %call = call i32 @lzma_lzma_encode(%struct.lzma_coder_s* %2, %struct.lzma_mf_s* %3, i8* %4, i64* %5, i64 %6, i32 -1), !dbg !2569
  store i32 %call, i32* %retval, align 4, !dbg !2570
  br label %return, !dbg !2570

return:                                           ; preds = %if.end, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !2571
  ret i32 %7, !dbg !2571
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readnone uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!510, !511}
!llvm.ident = !{!512}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !97, subprograms: !100)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/lzma_encoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !54, !69, !75, !80, !87, !90}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 57, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/base.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17}
!6 = !DIEnumerator(name: "LZMA_OK", value: 0)
!7 = !DIEnumerator(name: "LZMA_STREAM_END", value: 1)
!8 = !DIEnumerator(name: "LZMA_NO_CHECK", value: 2)
!9 = !DIEnumerator(name: "LZMA_UNSUPPORTED_CHECK", value: 3)
!10 = !DIEnumerator(name: "LZMA_GET_CHECK", value: 4)
!11 = !DIEnumerator(name: "LZMA_MEM_ERROR", value: 5)
!12 = !DIEnumerator(name: "LZMA_MEMLIMIT_ERROR", value: 6)
!13 = !DIEnumerator(name: "LZMA_FORMAT_ERROR", value: 7)
!14 = !DIEnumerator(name: "LZMA_OPTIONS_ERROR", value: 8)
!15 = !DIEnumerator(name: "LZMA_DATA_ERROR", value: 9)
!16 = !DIEnumerator(name: "LZMA_BUF_ERROR", value: 10)
!17 = !DIEnumerator(name: "LZMA_PROG_ERROR", value: 11)
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !20, file: !19, line: 40, size: 32, align: 32, elements: !48)
!19 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/rangecoder/range_encoder.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!20 = !DICompositeType(tag: DW_TAG_structure_type, file: !19, line: 27, size: 5888, align: 64, elements: !21)
!21 = !{!22, !26, !27, !30, !33, !36, !37, !41}
!22 = !DIDerivedType(tag: DW_TAG_member, name: "low", scope: !20, file: !19, line: 28, baseType: !23, size: 64, align: 64)
!23 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !24, line: 55, baseType: !25)
!24 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!25 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "cache_size", scope: !20, file: !19, line: 29, baseType: !23, size: 64, align: 64, offset: 64)
!27 = !DIDerivedType(tag: DW_TAG_member, name: "range", scope: !20, file: !19, line: 30, baseType: !28, size: 32, align: 32, offset: 128)
!28 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !24, line: 51, baseType: !29)
!29 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!30 = !DIDerivedType(tag: DW_TAG_member, name: "cache", scope: !20, file: !19, line: 31, baseType: !31, size: 8, align: 8, offset: 160)
!31 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !24, line: 48, baseType: !32)
!32 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "count", scope: !20, file: !19, line: 34, baseType: !34, size: 64, align: 64, offset: 192)
!34 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !35, line: 62, baseType: !25)
!35 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!36 = !DIDerivedType(tag: DW_TAG_member, name: "pos", scope: !20, file: !19, line: 37, baseType: !34, size: 64, align: 64, offset: 256)
!37 = !DIDerivedType(tag: DW_TAG_member, name: "symbols", scope: !20, file: !19, line: 46, baseType: !38, size: 1856, align: 32, offset: 320)
!38 = !DICompositeType(tag: DW_TAG_array_type, baseType: !18, size: 1856, align: 32, elements: !39)
!39 = !{!40}
!40 = !DISubrange(count: 58)
!41 = !DIDerivedType(tag: DW_TAG_member, name: "probs", scope: !20, file: !19, line: 49, baseType: !42, size: 3712, align: 64, offset: 2176)
!42 = !DICompositeType(tag: DW_TAG_array_type, baseType: !43, size: 3712, align: 64, elements: !39)
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!44 = !DIDerivedType(tag: DW_TAG_typedef, name: "probability", file: !45, line: 72, baseType: !46)
!45 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/rangecoder/range_common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!46 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint16_t", file: !24, line: 49, baseType: !47)
!47 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!48 = !{!49, !50, !51, !52, !53}
!49 = !DIEnumerator(name: "RC_BIT_0", value: 0)
!50 = !DIEnumerator(name: "RC_BIT_1", value: 1)
!51 = !DIEnumerator(name: "RC_DIRECT_0", value: 2)
!52 = !DIEnumerator(name: "RC_DIRECT_1", value: 3)
!53 = !DIEnumerator(name: "RC_FLUSH", value: 4)
!54 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !55, line: 56, size: 32, align: 32, elements: !56)
!55 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/lzma_common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!56 = !{!57, !58, !59, !60, !61, !62, !63, !64, !65, !66, !67, !68}
!57 = !DIEnumerator(name: "STATE_LIT_LIT", value: 0)
!58 = !DIEnumerator(name: "STATE_MATCH_LIT_LIT", value: 1)
!59 = !DIEnumerator(name: "STATE_REP_LIT_LIT", value: 2)
!60 = !DIEnumerator(name: "STATE_SHORTREP_LIT_LIT", value: 3)
!61 = !DIEnumerator(name: "STATE_MATCH_LIT", value: 4)
!62 = !DIEnumerator(name: "STATE_REP_LIT", value: 5)
!63 = !DIEnumerator(name: "STATE_SHORTREP_LIT", value: 6)
!64 = !DIEnumerator(name: "STATE_LIT_MATCH", value: 7)
!65 = !DIEnumerator(name: "STATE_LIT_LONGREP", value: 8)
!66 = !DIEnumerator(name: "STATE_LIT_SHORTREP", value: 9)
!67 = !DIEnumerator(name: "STATE_NONLIT_MATCH", value: 10)
!68 = !DIEnumerator(name: "STATE_NONLIT_REP", value: 11)
!69 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 250, size: 32, align: 32, elements: !70)
!70 = !{!71, !72, !73, !74}
!71 = !DIEnumerator(name: "LZMA_RUN", value: 0)
!72 = !DIEnumerator(name: "LZMA_SYNC_FLUSH", value: 1)
!73 = !DIEnumerator(name: "LZMA_FULL_FLUSH", value: 2)
!74 = !DIEnumerator(name: "LZMA_FINISH", value: 3)
!75 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !76, line: 138, size: 32, align: 32, elements: !77)
!76 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/lzma.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!77 = !{!78, !79}
!78 = !DIEnumerator(name: "LZMA_MODE_FAST", value: 1)
!79 = !DIEnumerator(name: "LZMA_MODE_NORMAL", value: 2)
!80 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !76, line: 58, size: 32, align: 32, elements: !81)
!81 = !{!82, !83, !84, !85, !86}
!82 = !DIEnumerator(name: "LZMA_MF_HC3", value: 3)
!83 = !DIEnumerator(name: "LZMA_MF_HC4", value: 4)
!84 = !DIEnumerator(name: "LZMA_MF_BT2", value: 18)
!85 = !DIEnumerator(name: "LZMA_MF_BT3", value: 19)
!86 = !DIEnumerator(name: "LZMA_MF_BT4", value: 20)
!87 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 44, size: 32, align: 32, elements: !88)
!88 = !{!89}
!89 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!90 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !91, line: 27, size: 32, align: 32, elements: !92)
!91 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!92 = !{!93, !94, !95, !96}
!93 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!94 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!95 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!96 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!97 = !{!98, !23, !28, !31, !99}
!98 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!99 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!100 = !{!101, !258, !295, !325, !383, !388, !391, !394, !398, !401, !402, !406, !409, !414, !417, !418, !423, !426, !429, !430, !434, !439, !442, !447, !448, !453, !456, !457, !461, !462, !465, !468, !471, !474, !475, !481, !484, !487, !504, !505, !506}
!101 = distinct !DISubprogram(name: "lzma_lzma_encode", scope: !1, file: !1, line: 321, type: !102, isLocal: false, isDefinition: true, scopeLine: 324, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!102 = !DISubroutineType(types: !103)
!103 = !{!104, !105, !217, !254, !255, !34, !28}
!104 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!105 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !106)
!106 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !107, size: 64, align: 64)
!107 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !108, line: 73, baseType: !109)
!108 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!109 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !110, line: 72, size: 1996608, align: 64, elements: !111)
!110 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/lzma_encoder_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!111 = !{!112, !114, !116, !120, !130, !131, !132, !134, !135, !136, !137, !138, !139, !144, !148, !151, !152, !153, !154, !155, !159, !163, !166, !188, !189, !191, !195, !196, !197, !198, !199, !200, !201}
!112 = !DIDerivedType(tag: DW_TAG_member, name: "rc", scope: !109, file: !110, line: 74, baseType: !113, size: 5888, align: 64)
!113 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_range_encoder", file: !19, line: 51, baseType: !20)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !109, file: !110, line: 77, baseType: !115, size: 32, align: 32, offset: 5888)
!115 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_lzma_state", file: !55, line: 69, baseType: !54)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "reps", scope: !109, file: !110, line: 80, baseType: !117, size: 128, align: 32, offset: 5920)
!117 = !DICompositeType(tag: DW_TAG_array_type, baseType: !28, size: 128, align: 32, elements: !118)
!118 = !{!119}
!119 = !DISubrange(count: 4)
!120 = !DIDerivedType(tag: DW_TAG_member, name: "matches", scope: !109, file: !110, line: 83, baseType: !121, size: 17536, align: 32, offset: 6048)
!121 = !DICompositeType(tag: DW_TAG_array_type, baseType: !122, size: 17536, align: 32, elements: !128)
!122 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_match", file: !123, line: 25, baseType: !124)
!123 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lz/lz_encoder.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!124 = !DICompositeType(tag: DW_TAG_structure_type, file: !123, line: 22, size: 64, align: 32, elements: !125)
!125 = !{!126, !127}
!126 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !124, file: !123, line: 23, baseType: !28, size: 32, align: 32)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "dist", scope: !124, file: !123, line: 24, baseType: !28, size: 32, align: 32, offset: 32)
!128 = !{!129}
!129 = !DISubrange(count: 274)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "matches_count", scope: !109, file: !110, line: 86, baseType: !28, size: 32, align: 32, offset: 23584)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "longest_match_length", scope: !109, file: !110, line: 90, baseType: !28, size: 32, align: 32, offset: 23616)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "fast_mode", scope: !109, file: !110, line: 93, baseType: !133, size: 8, align: 8, offset: 23648)
!133 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "is_initialized", scope: !109, file: !110, line: 97, baseType: !133, size: 8, align: 8, offset: 23656)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "is_flushed", scope: !109, file: !110, line: 101, baseType: !133, size: 8, align: 8, offset: 23664)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "pos_mask", scope: !109, file: !110, line: 103, baseType: !28, size: 32, align: 32, offset: 23680)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "literal_context_bits", scope: !109, file: !110, line: 104, baseType: !28, size: 32, align: 32, offset: 23712)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "literal_pos_mask", scope: !109, file: !110, line: 105, baseType: !28, size: 32, align: 32, offset: 23744)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "literal", scope: !109, file: !110, line: 108, baseType: !140, size: 196608, align: 16, offset: 23776)
!140 = !DICompositeType(tag: DW_TAG_array_type, baseType: !44, size: 196608, align: 16, elements: !141)
!141 = !{!142, !143}
!142 = !DISubrange(count: 16)
!143 = !DISubrange(count: 768)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "is_match", scope: !109, file: !110, line: 109, baseType: !145, size: 3072, align: 16, offset: 220384)
!145 = !DICompositeType(tag: DW_TAG_array_type, baseType: !44, size: 3072, align: 16, elements: !146)
!146 = !{!147, !142}
!147 = !DISubrange(count: 12)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "is_rep", scope: !109, file: !110, line: 110, baseType: !149, size: 192, align: 16, offset: 223456)
!149 = !DICompositeType(tag: DW_TAG_array_type, baseType: !44, size: 192, align: 16, elements: !150)
!150 = !{!147}
!151 = !DIDerivedType(tag: DW_TAG_member, name: "is_rep0", scope: !109, file: !110, line: 111, baseType: !149, size: 192, align: 16, offset: 223648)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "is_rep1", scope: !109, file: !110, line: 112, baseType: !149, size: 192, align: 16, offset: 223840)
!153 = !DIDerivedType(tag: DW_TAG_member, name: "is_rep2", scope: !109, file: !110, line: 113, baseType: !149, size: 192, align: 16, offset: 224032)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "is_rep0_long", scope: !109, file: !110, line: 114, baseType: !145, size: 3072, align: 16, offset: 224224)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "pos_slot", scope: !109, file: !110, line: 115, baseType: !156, size: 4096, align: 16, offset: 227296)
!156 = !DICompositeType(tag: DW_TAG_array_type, baseType: !44, size: 4096, align: 16, elements: !157)
!157 = !{!119, !158}
!158 = !DISubrange(count: 64)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "pos_special", scope: !109, file: !110, line: 116, baseType: !160, size: 1824, align: 16, offset: 231392)
!160 = !DICompositeType(tag: DW_TAG_array_type, baseType: !44, size: 1824, align: 16, elements: !161)
!161 = !{!162}
!162 = !DISubrange(count: 114)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "pos_align", scope: !109, file: !110, line: 117, baseType: !164, size: 256, align: 16, offset: 233216)
!164 = !DICompositeType(tag: DW_TAG_array_type, baseType: !44, size: 256, align: 16, elements: !165)
!165 = !{!142}
!166 = !DIDerivedType(tag: DW_TAG_member, name: "match_len_encoder", scope: !109, file: !110, line: 121, baseType: !167, size: 148032, align: 32, offset: 233472)
!167 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_length_encoder", file: !110, line: 51, baseType: !168)
!168 = !DICompositeType(tag: DW_TAG_structure_type, file: !110, line: 40, size: 148032, align: 32, elements: !169)
!169 = !{!170, !171, !172, !176, !177, !181, !185, !186}
!170 = !DIDerivedType(tag: DW_TAG_member, name: "choice", scope: !168, file: !110, line: 41, baseType: !44, size: 16, align: 16)
!171 = !DIDerivedType(tag: DW_TAG_member, name: "choice2", scope: !168, file: !110, line: 42, baseType: !44, size: 16, align: 16, offset: 16)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "low", scope: !168, file: !110, line: 43, baseType: !173, size: 2048, align: 16, offset: 32)
!173 = !DICompositeType(tag: DW_TAG_array_type, baseType: !44, size: 2048, align: 16, elements: !174)
!174 = !{!142, !175}
!175 = !DISubrange(count: 8)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "mid", scope: !168, file: !110, line: 44, baseType: !173, size: 2048, align: 16, offset: 2080)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "high", scope: !168, file: !110, line: 45, baseType: !178, size: 4096, align: 16, offset: 4128)
!178 = !DICompositeType(tag: DW_TAG_array_type, baseType: !44, size: 4096, align: 16, elements: !179)
!179 = !{!180}
!180 = !DISubrange(count: 256)
!181 = !DIDerivedType(tag: DW_TAG_member, name: "prices", scope: !168, file: !110, line: 47, baseType: !182, size: 139264, align: 32, offset: 8224)
!182 = !DICompositeType(tag: DW_TAG_array_type, baseType: !28, size: 139264, align: 32, elements: !183)
!183 = !{!142, !184}
!184 = !DISubrange(count: 272)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "table_size", scope: !168, file: !110, line: 48, baseType: !28, size: 32, align: 32, offset: 147488)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "counters", scope: !168, file: !110, line: 49, baseType: !187, size: 512, align: 32, offset: 147520)
!187 = !DICompositeType(tag: DW_TAG_array_type, baseType: !28, size: 512, align: 32, elements: !165)
!188 = !DIDerivedType(tag: DW_TAG_member, name: "rep_len_encoder", scope: !109, file: !110, line: 122, baseType: !167, size: 148032, align: 32, offset: 381504)
!189 = !DIDerivedType(tag: DW_TAG_member, name: "pos_slot_prices", scope: !109, file: !110, line: 125, baseType: !190, size: 8192, align: 32, offset: 529536)
!190 = !DICompositeType(tag: DW_TAG_array_type, baseType: !28, size: 8192, align: 32, elements: !157)
!191 = !DIDerivedType(tag: DW_TAG_member, name: "distances_prices", scope: !109, file: !110, line: 126, baseType: !192, size: 16384, align: 32, offset: 537728)
!192 = !DICompositeType(tag: DW_TAG_array_type, baseType: !28, size: 16384, align: 32, elements: !193)
!193 = !{!119, !194}
!194 = !DISubrange(count: 128)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "dist_table_size", scope: !109, file: !110, line: 127, baseType: !28, size: 32, align: 32, offset: 554112)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "match_price_count", scope: !109, file: !110, line: 128, baseType: !28, size: 32, align: 32, offset: 554144)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "align_prices", scope: !109, file: !110, line: 130, baseType: !187, size: 512, align: 32, offset: 554176)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "align_price_count", scope: !109, file: !110, line: 131, baseType: !28, size: 32, align: 32, offset: 554688)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "opts_end_index", scope: !109, file: !110, line: 134, baseType: !28, size: 32, align: 32, offset: 554720)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "opts_current_index", scope: !109, file: !110, line: 135, baseType: !28, size: 32, align: 32, offset: 554752)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "opts", scope: !109, file: !110, line: 136, baseType: !202, size: 1441792, align: 32, offset: 554784)
!202 = !DICompositeType(tag: DW_TAG_array_type, baseType: !203, size: 1441792, align: 32, elements: !215)
!203 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_optimal", file: !110, line: 69, baseType: !204)
!204 = !DICompositeType(tag: DW_TAG_structure_type, file: !110, line: 54, size: 352, align: 32, elements: !205)
!205 = !{!206, !207, !208, !209, !210, !211, !212, !213, !214}
!206 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !204, file: !110, line: 55, baseType: !115, size: 32, align: 32)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "prev_1_is_literal", scope: !204, file: !110, line: 57, baseType: !133, size: 8, align: 8, offset: 32)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "prev_2", scope: !204, file: !110, line: 58, baseType: !133, size: 8, align: 8, offset: 40)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "pos_prev_2", scope: !204, file: !110, line: 60, baseType: !28, size: 32, align: 32, offset: 64)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "back_prev_2", scope: !204, file: !110, line: 61, baseType: !28, size: 32, align: 32, offset: 96)
!211 = !DIDerivedType(tag: DW_TAG_member, name: "price", scope: !204, file: !110, line: 63, baseType: !28, size: 32, align: 32, offset: 128)
!212 = !DIDerivedType(tag: DW_TAG_member, name: "pos_prev", scope: !204, file: !110, line: 64, baseType: !28, size: 32, align: 32, offset: 160)
!213 = !DIDerivedType(tag: DW_TAG_member, name: "back_prev", scope: !204, file: !110, line: 65, baseType: !28, size: 32, align: 32, offset: 192)
!214 = !DIDerivedType(tag: DW_TAG_member, name: "backs", scope: !204, file: !110, line: 67, baseType: !117, size: 128, align: 32, offset: 224)
!215 = !{!216}
!216 = !DISubrange(count: 4096)
!217 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !218)
!218 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !219, size: 64, align: 64)
!219 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_mf", file: !123, line: 28, baseType: !220)
!220 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_mf_s", file: !123, line: 29, size: 960, align: 64, elements: !221)
!221 = !{!222, !224, !225, !226, !227, !228, !229, !230, !231, !232, !233, !238, !242, !243, !244, !245, !246, !247, !248, !249, !250, !252, !253}
!222 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !220, file: !123, line: 35, baseType: !223, size: 64, align: 64)
!223 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64, align: 64)
!224 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !220, file: !123, line: 39, baseType: !28, size: 32, align: 32, offset: 64)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "keep_size_before", scope: !220, file: !123, line: 45, baseType: !28, size: 32, align: 32, offset: 96)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "keep_size_after", scope: !220, file: !123, line: 51, baseType: !28, size: 32, align: 32, offset: 128)
!227 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !220, file: !123, line: 58, baseType: !28, size: 32, align: 32, offset: 160)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "read_pos", scope: !220, file: !123, line: 63, baseType: !28, size: 32, align: 32, offset: 192)
!229 = !DIDerivedType(tag: DW_TAG_member, name: "read_ahead", scope: !220, file: !123, line: 67, baseType: !28, size: 32, align: 32, offset: 224)
!230 = !DIDerivedType(tag: DW_TAG_member, name: "read_limit", scope: !220, file: !123, line: 75, baseType: !28, size: 32, align: 32, offset: 256)
!231 = !DIDerivedType(tag: DW_TAG_member, name: "write_pos", scope: !220, file: !123, line: 80, baseType: !28, size: 32, align: 32, offset: 288)
!232 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !220, file: !123, line: 84, baseType: !28, size: 32, align: 32, offset: 320)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "find", scope: !220, file: !123, line: 92, baseType: !234, size: 64, align: 64, offset: 384)
!234 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !235, size: 64, align: 64)
!235 = !DISubroutineType(types: !236)
!236 = !{!28, !218, !237}
!237 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !122, size: 64, align: 64)
!238 = !DIDerivedType(tag: DW_TAG_member, name: "skip", scope: !220, file: !123, line: 97, baseType: !239, size: 64, align: 64, offset: 448)
!239 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !240, size: 64, align: 64)
!240 = !DISubroutineType(types: !241)
!241 = !{null, !218, !28}
!242 = !DIDerivedType(tag: DW_TAG_member, name: "hash", scope: !220, file: !123, line: 99, baseType: !99, size: 64, align: 64, offset: 512)
!243 = !DIDerivedType(tag: DW_TAG_member, name: "son", scope: !220, file: !123, line: 100, baseType: !99, size: 64, align: 64, offset: 576)
!244 = !DIDerivedType(tag: DW_TAG_member, name: "cyclic_pos", scope: !220, file: !123, line: 101, baseType: !28, size: 32, align: 32, offset: 640)
!245 = !DIDerivedType(tag: DW_TAG_member, name: "cyclic_size", scope: !220, file: !123, line: 102, baseType: !28, size: 32, align: 32, offset: 672)
!246 = !DIDerivedType(tag: DW_TAG_member, name: "hash_mask", scope: !220, file: !123, line: 103, baseType: !28, size: 32, align: 32, offset: 704)
!247 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !220, file: !123, line: 106, baseType: !28, size: 32, align: 32, offset: 736)
!248 = !DIDerivedType(tag: DW_TAG_member, name: "nice_len", scope: !220, file: !123, line: 109, baseType: !28, size: 32, align: 32, offset: 768)
!249 = !DIDerivedType(tag: DW_TAG_member, name: "match_len_max", scope: !220, file: !123, line: 114, baseType: !28, size: 32, align: 32, offset: 800)
!250 = !DIDerivedType(tag: DW_TAG_member, name: "action", scope: !220, file: !123, line: 119, baseType: !251, size: 32, align: 32, offset: 832)
!251 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !69)
!252 = !DIDerivedType(tag: DW_TAG_member, name: "hash_size_sum", scope: !220, file: !123, line: 122, baseType: !28, size: 32, align: 32, offset: 864)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "sons_count", scope: !220, file: !123, line: 125, baseType: !28, size: 32, align: 32, offset: 896)
!254 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !223)
!255 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !256)
!256 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !34, size: 64, align: 64)
!257 = !{}
!258 = distinct !DISubprogram(name: "lzma_lzma_encoder_reset", scope: !1, file: !1, line: 490, type: !259, isLocal: false, isDefinition: true, scopeLine: 491, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!259 = !DISubroutineType(types: !260)
!260 = !{!104, !106, !261}
!261 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !262, size: 64, align: 64)
!262 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !263)
!263 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_options_lzma", file: !76, line: 399, baseType: !264)
!264 = !DICompositeType(tag: DW_TAG_structure_type, file: !76, line: 185, size: 896, align: 64, elements: !265)
!265 = !{!266, !267, !270, !271, !272, !273, !274, !276, !277, !279, !280, !281, !282, !283, !284, !285, !286, !287, !288, !290, !291, !292, !293, !294}
!266 = !DIDerivedType(tag: DW_TAG_member, name: "dict_size", scope: !264, file: !76, line: 217, baseType: !28, size: 32, align: 32)
!267 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict", scope: !264, file: !76, line: 240, baseType: !268, size: 64, align: 64, offset: 64)
!268 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !269, size: 64, align: 64)
!269 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !31)
!270 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict_size", scope: !264, file: !76, line: 254, baseType: !28, size: 32, align: 32, offset: 128)
!271 = !DIDerivedType(tag: DW_TAG_member, name: "lc", scope: !264, file: !76, line: 281, baseType: !28, size: 32, align: 32, offset: 160)
!272 = !DIDerivedType(tag: DW_TAG_member, name: "lp", scope: !264, file: !76, line: 293, baseType: !28, size: 32, align: 32, offset: 192)
!273 = !DIDerivedType(tag: DW_TAG_member, name: "pb", scope: !264, file: !76, line: 316, baseType: !28, size: 32, align: 32, offset: 224)
!274 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !264, file: !76, line: 322, baseType: !275, size: 32, align: 32, offset: 256)
!275 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_mode", file: !76, line: 155, baseType: !75)
!276 = !DIDerivedType(tag: DW_TAG_member, name: "nice_len", scope: !264, file: !76, line: 342, baseType: !28, size: 32, align: 32, offset: 288)
!277 = !DIDerivedType(tag: DW_TAG_member, name: "mf", scope: !264, file: !76, line: 345, baseType: !278, size: 32, align: 32, offset: 320)
!278 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_match_finder", file: !76, line: 111, baseType: !80)
!279 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !264, file: !76, line: 375, baseType: !28, size: 32, align: 32, offset: 352)
!280 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !264, file: !76, line: 384, baseType: !28, size: 32, align: 32, offset: 384)
!281 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !264, file: !76, line: 385, baseType: !28, size: 32, align: 32, offset: 416)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !264, file: !76, line: 386, baseType: !28, size: 32, align: 32, offset: 448)
!283 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !264, file: !76, line: 387, baseType: !28, size: 32, align: 32, offset: 480)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int5", scope: !264, file: !76, line: 388, baseType: !28, size: 32, align: 32, offset: 512)
!285 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int6", scope: !264, file: !76, line: 389, baseType: !28, size: 32, align: 32, offset: 544)
!286 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int7", scope: !264, file: !76, line: 390, baseType: !28, size: 32, align: 32, offset: 576)
!287 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int8", scope: !264, file: !76, line: 391, baseType: !28, size: 32, align: 32, offset: 608)
!288 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !264, file: !76, line: 392, baseType: !289, size: 32, align: 32, offset: 640)
!289 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !87)
!290 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !264, file: !76, line: 393, baseType: !289, size: 32, align: 32, offset: 672)
!291 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !264, file: !76, line: 394, baseType: !289, size: 32, align: 32, offset: 704)
!292 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !264, file: !76, line: 395, baseType: !289, size: 32, align: 32, offset: 736)
!293 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !264, file: !76, line: 396, baseType: !98, size: 64, align: 64, offset: 768)
!294 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !264, file: !76, line: 397, baseType: !98, size: 64, align: 64, offset: 832)
!295 = distinct !DISubprogram(name: "lzma_lzma_encoder_create", scope: !1, file: !1, line: 564, type: !296, isLocal: false, isDefinition: true, scopeLine: 566, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!296 = !DISubroutineType(types: !297)
!297 = !{!104, !298, !299, !261, !312}
!298 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !106, size: 64, align: 64)
!299 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !300, size: 64, align: 64)
!300 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !301)
!301 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !302)
!302 = !{!303, !307, !311}
!303 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !301, file: !4, line: 376, baseType: !304, size: 64, align: 64)
!304 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !305, size: 64, align: 64)
!305 = !DISubroutineType(types: !306)
!306 = !{!98, !98, !34, !34}
!307 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !301, file: !4, line: 390, baseType: !308, size: 64, align: 64, offset: 64)
!308 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !309, size: 64, align: 64)
!309 = !DISubroutineType(types: !310)
!310 = !{null, !98, !98}
!311 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !301, file: !4, line: 401, baseType: !98, size: 64, align: 64, offset: 128)
!312 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !313, size: 64, align: 64)
!313 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_lz_options", file: !123, line: 161, baseType: !314)
!314 = !DICompositeType(tag: DW_TAG_structure_type, file: !123, line: 129, size: 512, align: 64, elements: !315)
!315 = !{!316, !317, !318, !319, !320, !321, !322, !323, !324}
!316 = !DIDerivedType(tag: DW_TAG_member, name: "before_size", scope: !314, file: !123, line: 132, baseType: !34, size: 64, align: 64)
!317 = !DIDerivedType(tag: DW_TAG_member, name: "dict_size", scope: !314, file: !123, line: 135, baseType: !34, size: 64, align: 64, offset: 64)
!318 = !DIDerivedType(tag: DW_TAG_member, name: "after_size", scope: !314, file: !123, line: 139, baseType: !34, size: 64, align: 64, offset: 128)
!319 = !DIDerivedType(tag: DW_TAG_member, name: "match_len_max", scope: !314, file: !123, line: 144, baseType: !34, size: 64, align: 64, offset: 192)
!320 = !DIDerivedType(tag: DW_TAG_member, name: "nice_len", scope: !314, file: !123, line: 148, baseType: !34, size: 64, align: 64, offset: 256)
!321 = !DIDerivedType(tag: DW_TAG_member, name: "match_finder", scope: !314, file: !123, line: 151, baseType: !278, size: 32, align: 32, offset: 320)
!322 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !314, file: !123, line: 154, baseType: !28, size: 32, align: 32, offset: 352)
!323 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict", scope: !314, file: !123, line: 157, baseType: !268, size: 64, align: 64, offset: 384)
!324 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict_size", scope: !314, file: !123, line: 159, baseType: !28, size: 32, align: 32, offset: 448)
!325 = distinct !DISubprogram(name: "lzma_lzma_encoder_init", scope: !1, file: !1, line: 635, type: !326, isLocal: false, isDefinition: true, scopeLine: 637, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!326 = !DISubroutineType(types: !327)
!327 = !{!104, !328, !299, !373}
!328 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !329, size: 64, align: 64)
!329 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !108, line: 75, baseType: !330)
!330 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !108, line: 119, size: 512, align: 64, elements: !331)
!331 = !{!332, !333, !336, !338, !344, !349, !356, !361}
!332 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !330, file: !108, line: 121, baseType: !106, size: 64, align: 64)
!333 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !330, file: !108, line: 125, baseType: !334, size: 64, align: 64, offset: 64)
!334 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !335, line: 63, baseType: !23)
!335 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!336 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !330, file: !108, line: 131, baseType: !337, size: 64, align: 64, offset: 128)
!337 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !24, line: 122, baseType: !25)
!338 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !330, file: !108, line: 134, baseType: !339, size: 64, align: 64, offset: 192)
!339 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !108, line: 89, baseType: !340)
!340 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !341, size: 64, align: 64)
!341 = !DISubroutineType(types: !342)
!342 = !{!104, !106, !299, !343, !255, !34, !254, !255, !34, !251}
!343 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !268)
!344 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !330, file: !108, line: 139, baseType: !345, size: 64, align: 64, offset: 256)
!345 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !108, line: 97, baseType: !346)
!346 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !347, size: 64, align: 64)
!347 = !DISubroutineType(types: !348)
!348 = !{null, !106, !299}
!349 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !330, file: !108, line: 143, baseType: !350, size: 64, align: 64, offset: 320)
!350 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !351, size: 64, align: 64)
!351 = !DISubroutineType(types: !352)
!352 = !{!353, !354}
!353 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !91, line: 55, baseType: !90)
!354 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !355, size: 64, align: 64)
!355 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !107)
!356 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !330, file: !108, line: 147, baseType: !357, size: 64, align: 64, offset: 384)
!357 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !358, size: 64, align: 64)
!358 = !DISubroutineType(types: !359)
!359 = !{!104, !106, !360, !360, !23}
!360 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !23, size: 64, align: 64)
!361 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !330, file: !108, line: 152, baseType: !362, size: 64, align: 64, offset: 448)
!362 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !363, size: 64, align: 64)
!363 = !DISubroutineType(types: !364)
!364 = !{!104, !106, !299, !365, !365}
!365 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !366, size: 64, align: 64)
!366 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !367)
!367 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !368, line: 65, baseType: !369)
!368 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!369 = !DICompositeType(tag: DW_TAG_structure_type, file: !368, line: 43, size: 128, align: 64, elements: !370)
!370 = !{!371, !372}
!371 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !369, file: !368, line: 54, baseType: !334, size: 64, align: 64)
!372 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !369, file: !368, line: 63, baseType: !98, size: 64, align: 64, offset: 64)
!373 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !374, size: 64, align: 64)
!374 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !375)
!375 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter_info", file: !108, line: 77, baseType: !376)
!376 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_filter_info_s", file: !108, line: 104, size: 192, align: 64, elements: !377)
!377 = !{!378, !379, !382}
!378 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !376, file: !108, line: 107, baseType: !334, size: 64, align: 64)
!379 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !376, file: !108, line: 111, baseType: !380, size: 64, align: 64, offset: 64)
!380 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_init_function", file: !108, line: 81, baseType: !381)
!381 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !326, size: 64, align: 64)
!382 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !376, file: !108, line: 114, baseType: !98, size: 64, align: 64, offset: 128)
!383 = distinct !DISubprogram(name: "lzma_lzma_encoder_memusage", scope: !1, file: !1, line: 644, type: !384, isLocal: false, isDefinition: true, scopeLine: 645, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!384 = !DISubroutineType(types: !385)
!385 = !{!23, !386}
!386 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !387, size: 64, align: 64)
!387 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!388 = distinct !DISubprogram(name: "lzma_lzma_lclppb_encode", scope: !1, file: !1, line: 663, type: !389, isLocal: false, isDefinition: true, scopeLine: 664, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!389 = !DISubroutineType(types: !390)
!390 = !{!133, !261, !223}
!391 = distinct !DISubprogram(name: "lzma_lzma_props_encode", scope: !1, file: !1, line: 677, type: !392, isLocal: false, isDefinition: true, scopeLine: 678, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!392 = !DISubroutineType(types: !393)
!393 = !{!104, !386, !223}
!394 = distinct !DISubprogram(name: "lzma_mode_is_supported", scope: !1, file: !1, line: 692, type: !395, isLocal: false, isDefinition: true, scopeLine: 693, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!395 = !DISubroutineType(types: !396)
!396 = !{!397, !275}
!397 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_bool", file: !4, line: 29, baseType: !32)
!398 = distinct !DISubprogram(name: "encode_init", scope: !1, file: !1, line: 277, type: !399, isLocal: true, isDefinition: true, scopeLine: 278, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!399 = !DISubroutineType(types: !400)
!400 = !{!133, !106, !218}
!401 = distinct !DISubprogram(name: "mf_skip", scope: !123, file: !123, line: 268, type: !240, isLocal: true, isDefinition: true, scopeLine: 269, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!402 = distinct !DISubprogram(name: "rc_bit", scope: !19, file: !19, line: 67, type: !403, isLocal: true, isDefinition: true, scopeLine: 68, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!403 = !DISubroutineType(types: !404)
!404 = !{null, !405, !43, !28}
!405 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !113, size: 64, align: 64)
!406 = distinct !DISubprogram(name: "rc_bittree", scope: !19, file: !19, line: 76, type: !407, isLocal: true, isDefinition: true, scopeLine: 78, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!407 = !DISubroutineType(types: !408)
!408 = !{null, !405, !43, !28, !28}
!409 = distinct !DISubprogram(name: "mf_position", scope: !123, file: !123, line: 253, type: !410, isLocal: true, isDefinition: true, scopeLine: 254, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!410 = !DISubroutineType(types: !411)
!411 = !{!28, !412}
!412 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !413, size: 64, align: 64)
!413 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !219)
!414 = distinct !DISubprogram(name: "rc_encode", scope: !19, file: !19, line: 151, type: !415, isLocal: true, isDefinition: true, scopeLine: 153, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!415 = !DISubroutineType(types: !416)
!416 = !{!133, !405, !223, !256, !34}
!417 = distinct !DISubprogram(name: "rc_shift_low", scope: !19, file: !19, line: 125, type: !415, isLocal: true, isDefinition: true, scopeLine: 127, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!418 = distinct !DISubprogram(name: "rc_pending", scope: !19, file: !19, line: 227, type: !419, isLocal: true, isDefinition: true, scopeLine: 228, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!419 = !DISubroutineType(types: !420)
!420 = !{!23, !421}
!421 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !422, size: 64, align: 64)
!422 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !113)
!423 = distinct !DISubprogram(name: "encode_symbol", scope: !1, file: !1, line: 243, type: !424, isLocal: true, isDefinition: true, scopeLine: 245, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!424 = !DISubroutineType(types: !425)
!425 = !{null, !106, !218, !28, !28, !28}
!426 = distinct !DISubprogram(name: "literal", scope: !1, file: !1, line: 49, type: !427, isLocal: true, isDefinition: true, scopeLine: 50, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!427 = !DISubroutineType(types: !428)
!428 = !{null, !106, !218, !28}
!429 = distinct !DISubprogram(name: "literal_matched", scope: !1, file: !1, line: 24, type: !407, isLocal: true, isDefinition: true, scopeLine: 26, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!430 = distinct !DISubprogram(name: "rep_match", scope: !1, file: !1, line: 199, type: !431, isLocal: true, isDefinition: true, scopeLine: 201, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!431 = !DISubroutineType(types: !432)
!432 = !{null, !106, !433, !433, !433}
!433 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !28)
!434 = distinct !DISubprogram(name: "length", scope: !1, file: !1, line: 113, type: !435, isLocal: true, isDefinition: true, scopeLine: 115, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!435 = !DISubroutineType(types: !436)
!436 = !{null, !405, !437, !433, !28, !438}
!437 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !167, size: 64, align: 64)
!438 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !133)
!439 = distinct !DISubprogram(name: "length_update_prices", scope: !1, file: !1, line: 81, type: !440, isLocal: true, isDefinition: true, scopeLine: 82, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!440 = !DISubroutineType(types: !441)
!441 = !{null, !437, !433}
!442 = distinct !DISubprogram(name: "rc_bit_0_price", scope: !443, file: !443, line: 37, type: !444, isLocal: true, isDefinition: true, scopeLine: 38, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!443 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/rangecoder/price.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!444 = !DISubroutineType(types: !445)
!445 = !{!28, !446}
!446 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !44)
!447 = distinct !DISubprogram(name: "rc_bit_1_price", scope: !443, file: !443, line: 44, type: !444, isLocal: true, isDefinition: true, scopeLine: 45, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!448 = distinct !DISubprogram(name: "rc_bittree_price", scope: !443, file: !443, line: 52, type: !449, isLocal: true, isDefinition: true, scopeLine: 54, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!449 = !DISubroutineType(types: !450)
!450 = !{!28, !451, !433, !28}
!451 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !452)
!452 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !446, size: 64, align: 64)
!453 = distinct !DISubprogram(name: "rc_bit_price", scope: !443, file: !443, line: 29, type: !454, isLocal: true, isDefinition: true, scopeLine: 30, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!454 = !DISubroutineType(types: !455)
!455 = !{!28, !446, !433}
!456 = distinct !DISubprogram(name: "match", scope: !1, file: !1, line: 149, type: !431, isLocal: true, isDefinition: true, scopeLine: 151, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!457 = distinct !DISubprogram(name: "get_pos_slot", scope: !458, file: !458, line: 110, type: !459, isLocal: true, isDefinition: true, scopeLine: 111, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!458 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/lzma/fastpos.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!459 = !DISubroutineType(types: !460)
!460 = !{!28, !28}
!461 = distinct !DISubprogram(name: "rc_bittree_reverse", scope: !19, file: !19, line: 90, type: !407, isLocal: true, isDefinition: true, scopeLine: 92, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!462 = distinct !DISubprogram(name: "rc_direct", scope: !19, file: !19, line: 105, type: !463, isLocal: true, isDefinition: true, scopeLine: 107, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!463 = !DISubroutineType(types: !464)
!464 = !{null, !405, !28, !28}
!465 = distinct !DISubprogram(name: "encode_eopm", scope: !1, file: !1, line: 305, type: !466, isLocal: true, isDefinition: true, scopeLine: 306, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!466 = !DISubroutineType(types: !467)
!467 = !{null, !106, !28}
!468 = distinct !DISubprogram(name: "rc_flush", scope: !19, file: !19, line: 116, type: !469, isLocal: true, isDefinition: true, scopeLine: 117, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!469 = !DISubroutineType(types: !470)
!470 = !{null, !405}
!471 = distinct !DISubprogram(name: "is_options_valid", scope: !1, file: !1, line: 434, type: !472, isLocal: true, isDefinition: true, scopeLine: 435, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!472 = !DISubroutineType(types: !473)
!473 = !{!133, !261}
!474 = distinct !DISubprogram(name: "rc_reset", scope: !19, file: !19, line: 55, type: !469, isLocal: true, isDefinition: true, scopeLine: 56, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!475 = distinct !DISubprogram(name: "literal_init", scope: !55, file: !55, line: 129, type: !476, isLocal: true, isDefinition: true, scopeLine: 131, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!476 = !DISubroutineType(types: !477)
!477 = !{null, !478, !28, !28}
!478 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !479, size: 64, align: 64)
!479 = !DICompositeType(tag: DW_TAG_array_type, baseType: !44, size: 12288, align: 16, elements: !480)
!480 = !{!143}
!481 = distinct !DISubprogram(name: "length_encoder_reset", scope: !1, file: !1, line: 465, type: !482, isLocal: true, isDefinition: true, scopeLine: 467, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!482 = !DISubroutineType(types: !483)
!483 = !{null, !437, !433, !438}
!484 = distinct !DISubprogram(name: "set_lz_options", scope: !1, file: !1, line: 447, type: !485, isLocal: true, isDefinition: true, scopeLine: 448, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!485 = !DISubroutineType(types: !486)
!486 = !{null, !312, !261}
!487 = distinct !DISubprogram(name: "lzma_encoder_init", scope: !1, file: !1, line: 625, type: !488, isLocal: true, isDefinition: true, scopeLine: 627, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!488 = !DISubroutineType(types: !489)
!489 = !{!104, !490, !299, !386, !312}
!490 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !491, size: 64, align: 64)
!491 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_lz_encoder", file: !123, line: 208, baseType: !492)
!492 = !DICompositeType(tag: DW_TAG_structure_type, file: !123, line: 192, size: 256, align: 64, elements: !493)
!493 = !{!494, !495, !499, !500}
!494 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !492, file: !123, line: 194, baseType: !106, size: 64, align: 64)
!495 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !492, file: !123, line: 197, baseType: !496, size: 64, align: 64, offset: 64)
!496 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !497, size: 64, align: 64)
!497 = !DISubroutineType(types: !498)
!498 = !{!104, !105, !217, !254, !255, !34}
!499 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !492, file: !123, line: 202, baseType: !346, size: 64, align: 64, offset: 128)
!500 = !DIDerivedType(tag: DW_TAG_member, name: "options_update", scope: !492, file: !123, line: 205, baseType: !501, size: 64, align: 64, offset: 192)
!501 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !502, size: 64, align: 64)
!502 = !DISubroutineType(types: !503)
!503 = !{!104, !106, !365}
!504 = distinct !DISubprogram(name: "lzma_encode", scope: !1, file: !1, line: 417, type: !497, isLocal: true, isDefinition: true, scopeLine: 420, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!505 = distinct !DISubprogram(name: "is_lclppb_valid", scope: !55, file: !55, line: 33, type: !472, isLocal: true, isDefinition: true, scopeLine: 34, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!506 = distinct !DISubprogram(name: "write32ne", scope: !507, file: !507, line: 255, type: !508, isLocal: true, isDefinition: true, scopeLine: 256, flags: DIFlagPrototyped, isOptimized: false, variables: !257)
!507 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/common/tuklib_integer.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!508 = !DISubroutineType(types: !509)
!509 = !{null, !223, !28}
!510 = !{i32 2, !"Dwarf Version", i32 4}
!511 = !{i32 2, !"Debug Info Version", i32 3}
!512 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!513 = !DILocalVariable(name: "coder", arg: 1, scope: !101, file: !1, line: 321, type: !105)
!514 = !DIExpression()
!515 = !DILocation(line: 321, column: 44, scope: !101)
!516 = !DILocalVariable(name: "mf", arg: 2, scope: !101, file: !1, line: 321, type: !217)
!517 = !DILocation(line: 321, column: 74, scope: !101)
!518 = !DILocalVariable(name: "out", arg: 3, scope: !101, file: !1, line: 322, type: !254)
!519 = !DILocation(line: 322, column: 26, scope: !101)
!520 = !DILocalVariable(name: "out_pos", arg: 4, scope: !101, file: !1, line: 322, type: !255)
!521 = !DILocation(line: 322, column: 53, scope: !101)
!522 = !DILocalVariable(name: "out_size", arg: 5, scope: !101, file: !1, line: 323, type: !34)
!523 = !DILocation(line: 323, column: 10, scope: !101)
!524 = !DILocalVariable(name: "limit", arg: 6, scope: !101, file: !1, line: 323, type: !28)
!525 = !DILocation(line: 323, column: 29, scope: !101)
!526 = !DILocalVariable(name: "position", scope: !101, file: !1, line: 325, type: !28)
!527 = !DILocation(line: 325, column: 11, scope: !101)
!528 = !DILocation(line: 328, column: 7, scope: !529)
!529 = distinct !DILexicalBlock(scope: !101, file: !1, line: 328, column: 6)
!530 = !DILocation(line: 328, column: 14, scope: !529)
!531 = !DILocation(line: 328, column: 29, scope: !529)
!532 = !DILocation(line: 328, column: 45, scope: !533)
!533 = !DILexicalBlockFile(scope: !529, file: !1, discriminator: 1)
!534 = !DILocation(line: 328, column: 52, scope: !533)
!535 = !DILocation(line: 328, column: 33, scope: !533)
!536 = !DILocation(line: 328, column: 6, scope: !533)
!537 = !DILocation(line: 329, column: 3, scope: !529)
!538 = !DILocation(line: 332, column: 25, scope: !101)
!539 = !DILocation(line: 332, column: 13, scope: !101)
!540 = !DILocation(line: 332, column: 11, scope: !101)
!541 = !DILocation(line: 334, column: 2, scope: !101)
!542 = !DILocalVariable(name: "len", scope: !543, file: !1, line: 335, type: !28)
!543 = distinct !DILexicalBlock(scope: !101, file: !1, line: 334, column: 15)
!544 = !DILocation(line: 335, column: 12, scope: !543)
!545 = !DILocalVariable(name: "back", scope: !543, file: !1, line: 336, type: !28)
!546 = !DILocation(line: 336, column: 12, scope: !543)
!547 = !DILocation(line: 344, column: 18, scope: !548)
!548 = distinct !DILexicalBlock(scope: !543, file: !1, line: 344, column: 7)
!549 = !DILocation(line: 344, column: 25, scope: !548)
!550 = !DILocation(line: 344, column: 29, scope: !548)
!551 = !DILocation(line: 344, column: 34, scope: !548)
!552 = !DILocation(line: 344, column: 43, scope: !548)
!553 = !DILocation(line: 344, column: 7, scope: !548)
!554 = !DILocation(line: 344, column: 7, scope: !543)
!555 = !DILocation(line: 345, column: 4, scope: !556)
!556 = distinct !DILexicalBlock(scope: !548, file: !1, line: 344, column: 54)
!557 = !DILocation(line: 345, column: 4, scope: !558)
!558 = !DILexicalBlockFile(scope: !556, file: !1, discriminator: 1)
!559 = !DILocation(line: 345, column: 4, scope: !560)
!560 = !DILexicalBlockFile(scope: !556, file: !1, discriminator: 2)
!561 = !DILocation(line: 345, column: 4, scope: !562)
!562 = !DILexicalBlockFile(scope: !556, file: !1, discriminator: 3)
!563 = !DILocation(line: 346, column: 4, scope: !556)
!564 = !DILocation(line: 352, column: 7, scope: !565)
!565 = distinct !DILexicalBlock(scope: !543, file: !1, line: 352, column: 7)
!566 = !DILocation(line: 352, column: 13, scope: !565)
!567 = !DILocation(line: 353, column: 5, scope: !565)
!568 = !DILocation(line: 353, column: 9, scope: !569)
!569 = !DILexicalBlockFile(scope: !565, file: !1, discriminator: 1)
!570 = !DILocation(line: 353, column: 13, scope: !569)
!571 = !DILocation(line: 353, column: 24, scope: !569)
!572 = !DILocation(line: 353, column: 28, scope: !569)
!573 = !DILocation(line: 353, column: 22, scope: !569)
!574 = !DILocation(line: 353, column: 42, scope: !569)
!575 = !DILocation(line: 353, column: 39, scope: !569)
!576 = !DILocation(line: 354, column: 6, scope: !565)
!577 = !DILocation(line: 354, column: 10, scope: !569)
!578 = !DILocation(line: 354, column: 9, scope: !569)
!579 = !DILocation(line: 354, column: 32, scope: !569)
!580 = !DILocation(line: 354, column: 39, scope: !569)
!581 = !DILocation(line: 354, column: 20, scope: !569)
!582 = !DILocation(line: 354, column: 18, scope: !569)
!583 = !DILocation(line: 355, column: 7, scope: !565)
!584 = !DILocation(line: 352, column: 7, scope: !585)
!585 = !DILexicalBlockFile(scope: !543, file: !1, discriminator: 1)
!586 = !DILocation(line: 357, column: 4, scope: !565)
!587 = !DILocation(line: 360, column: 7, scope: !588)
!588 = distinct !DILexicalBlock(scope: !543, file: !1, line: 360, column: 7)
!589 = !DILocation(line: 360, column: 11, scope: !588)
!590 = !DILocation(line: 360, column: 23, scope: !588)
!591 = !DILocation(line: 360, column: 27, scope: !588)
!592 = !DILocation(line: 360, column: 20, scope: !588)
!593 = !DILocation(line: 360, column: 7, scope: !543)
!594 = !DILocation(line: 361, column: 8, scope: !595)
!595 = distinct !DILexicalBlock(scope: !596, file: !1, line: 361, column: 8)
!596 = distinct !DILexicalBlock(scope: !588, file: !1, line: 360, column: 39)
!597 = !DILocation(line: 361, column: 12, scope: !595)
!598 = !DILocation(line: 361, column: 19, scope: !595)
!599 = !DILocation(line: 361, column: 8, scope: !596)
!600 = !DILocation(line: 362, column: 5, scope: !595)
!601 = !DILocation(line: 364, column: 8, scope: !602)
!602 = distinct !DILexicalBlock(scope: !596, file: !1, line: 364, column: 8)
!603 = !DILocation(line: 364, column: 12, scope: !602)
!604 = !DILocation(line: 364, column: 23, scope: !602)
!605 = !DILocation(line: 364, column: 8, scope: !596)
!606 = !DILocation(line: 365, column: 5, scope: !602)
!607 = !DILocation(line: 366, column: 3, scope: !596)
!608 = !DILocation(line: 377, column: 7, scope: !609)
!609 = distinct !DILexicalBlock(scope: !543, file: !1, line: 377, column: 7)
!610 = !DILocation(line: 377, column: 14, scope: !609)
!611 = !DILocation(line: 377, column: 7, scope: !543)
!612 = !DILocation(line: 378, column: 27, scope: !609)
!613 = !DILocation(line: 378, column: 34, scope: !609)
!614 = !DILocation(line: 378, column: 4, scope: !609)
!615 = !DILocation(line: 381, column: 6, scope: !609)
!616 = !DILocation(line: 381, column: 13, scope: !609)
!617 = !DILocation(line: 381, column: 30, scope: !609)
!618 = !DILocation(line: 380, column: 4, scope: !609)
!619 = !DILocation(line: 383, column: 17, scope: !543)
!620 = !DILocation(line: 383, column: 24, scope: !543)
!621 = !DILocation(line: 383, column: 28, scope: !543)
!622 = !DILocation(line: 383, column: 34, scope: !543)
!623 = !DILocation(line: 383, column: 39, scope: !543)
!624 = !DILocation(line: 383, column: 3, scope: !543)
!625 = !DILocation(line: 385, column: 15, scope: !543)
!626 = !DILocation(line: 385, column: 12, scope: !543)
!627 = !DILocation(line: 334, column: 2, scope: !628)
!628 = !DILexicalBlockFile(scope: !101, file: !1, discriminator: 1)
!629 = !DILocation(line: 388, column: 7, scope: !630)
!630 = distinct !DILexicalBlock(scope: !101, file: !1, line: 388, column: 6)
!631 = !DILocation(line: 388, column: 14, scope: !630)
!632 = !DILocation(line: 388, column: 6, scope: !101)
!633 = !DILocation(line: 389, column: 3, scope: !634)
!634 = distinct !DILexicalBlock(scope: !630, file: !1, line: 388, column: 26)
!635 = !DILocation(line: 389, column: 10, scope: !634)
!636 = !DILocation(line: 389, column: 21, scope: !634)
!637 = !DILocation(line: 393, column: 7, scope: !638)
!638 = distinct !DILexicalBlock(scope: !634, file: !1, line: 393, column: 7)
!639 = !DILocation(line: 393, column: 13, scope: !638)
!640 = !DILocation(line: 393, column: 7, scope: !634)
!641 = !DILocation(line: 394, column: 16, scope: !638)
!642 = !DILocation(line: 394, column: 23, scope: !638)
!643 = !DILocation(line: 394, column: 4, scope: !638)
!644 = !DILocation(line: 397, column: 13, scope: !634)
!645 = !DILocation(line: 397, column: 20, scope: !634)
!646 = !DILocation(line: 397, column: 3, scope: !634)
!647 = !DILocation(line: 403, column: 18, scope: !648)
!648 = distinct !DILexicalBlock(scope: !634, file: !1, line: 403, column: 7)
!649 = !DILocation(line: 403, column: 25, scope: !648)
!650 = !DILocation(line: 403, column: 29, scope: !648)
!651 = !DILocation(line: 403, column: 34, scope: !648)
!652 = !DILocation(line: 403, column: 43, scope: !648)
!653 = !DILocation(line: 403, column: 7, scope: !648)
!654 = !DILocation(line: 403, column: 7, scope: !634)
!655 = !DILocation(line: 404, column: 4, scope: !656)
!656 = distinct !DILexicalBlock(scope: !648, file: !1, line: 403, column: 54)
!657 = !DILocation(line: 404, column: 4, scope: !658)
!658 = !DILexicalBlockFile(scope: !656, file: !1, discriminator: 1)
!659 = !DILocation(line: 404, column: 4, scope: !660)
!660 = !DILexicalBlockFile(scope: !656, file: !1, discriminator: 2)
!661 = !DILocation(line: 404, column: 4, scope: !662)
!662 = !DILexicalBlockFile(scope: !656, file: !1, discriminator: 3)
!663 = !DILocation(line: 405, column: 4, scope: !656)
!664 = !DILocation(line: 407, column: 2, scope: !634)
!665 = !DILocation(line: 410, column: 2, scope: !101)
!666 = !DILocation(line: 410, column: 9, scope: !101)
!667 = !DILocation(line: 410, column: 20, scope: !101)
!668 = !DILocation(line: 412, column: 2, scope: !101)
!669 = !DILocation(line: 413, column: 1, scope: !101)
!670 = !DILocalVariable(name: "coder", arg: 1, scope: !398, file: !1, line: 277, type: !106)
!671 = !DILocation(line: 277, column: 25, scope: !398)
!672 = !DILocalVariable(name: "mf", arg: 2, scope: !398, file: !1, line: 277, type: !218)
!673 = !DILocation(line: 277, column: 41, scope: !398)
!674 = !DILocation(line: 279, column: 2, scope: !398)
!675 = !DILocation(line: 279, column: 2, scope: !676)
!676 = !DILexicalBlockFile(scope: !398, file: !1, discriminator: 1)
!677 = !DILocation(line: 279, column: 2, scope: !678)
!678 = !DILexicalBlockFile(scope: !398, file: !1, discriminator: 2)
!679 = !DILocation(line: 279, column: 2, scope: !680)
!680 = !DILexicalBlockFile(scope: !398, file: !1, discriminator: 3)
!681 = !DILocation(line: 281, column: 6, scope: !682)
!682 = distinct !DILexicalBlock(scope: !398, file: !1, line: 281, column: 6)
!683 = !DILocation(line: 281, column: 10, scope: !682)
!684 = !DILocation(line: 281, column: 22, scope: !682)
!685 = !DILocation(line: 281, column: 26, scope: !682)
!686 = !DILocation(line: 281, column: 19, scope: !682)
!687 = !DILocation(line: 281, column: 6, scope: !398)
!688 = !DILocation(line: 282, column: 7, scope: !689)
!689 = distinct !DILexicalBlock(scope: !690, file: !1, line: 282, column: 7)
!690 = distinct !DILexicalBlock(scope: !682, file: !1, line: 281, column: 38)
!691 = !DILocation(line: 282, column: 11, scope: !689)
!692 = !DILocation(line: 282, column: 18, scope: !689)
!693 = !DILocation(line: 282, column: 7, scope: !690)
!694 = !DILocation(line: 283, column: 4, scope: !689)
!695 = !DILocation(line: 286, column: 3, scope: !690)
!696 = !DILocation(line: 286, column: 3, scope: !697)
!697 = !DILexicalBlockFile(scope: !690, file: !1, discriminator: 1)
!698 = !DILocation(line: 286, column: 3, scope: !699)
!699 = !DILexicalBlockFile(scope: !690, file: !1, discriminator: 2)
!700 = !DILocation(line: 286, column: 3, scope: !701)
!701 = !DILexicalBlockFile(scope: !690, file: !1, discriminator: 3)
!702 = !DILocation(line: 287, column: 3, scope: !690)
!703 = !DILocation(line: 287, column: 3, scope: !697)
!704 = !DILocation(line: 287, column: 3, scope: !699)
!705 = !DILocation(line: 287, column: 3, scope: !701)
!706 = !DILocation(line: 288, column: 2, scope: !690)
!707 = !DILocation(line: 291, column: 11, scope: !708)
!708 = distinct !DILexicalBlock(scope: !682, file: !1, line: 288, column: 9)
!709 = !DILocation(line: 291, column: 3, scope: !708)
!710 = !DILocation(line: 292, column: 3, scope: !708)
!711 = !DILocation(line: 292, column: 7, scope: !708)
!712 = !DILocation(line: 292, column: 18, scope: !708)
!713 = !DILocation(line: 293, column: 11, scope: !708)
!714 = !DILocation(line: 293, column: 18, scope: !708)
!715 = !DILocation(line: 293, column: 23, scope: !708)
!716 = !DILocation(line: 293, column: 30, scope: !708)
!717 = !DILocation(line: 293, column: 3, scope: !708)
!718 = !DILocation(line: 294, column: 15, scope: !708)
!719 = !DILocation(line: 294, column: 22, scope: !708)
!720 = !DILocation(line: 294, column: 26, scope: !708)
!721 = !DILocation(line: 294, column: 33, scope: !708)
!722 = !DILocation(line: 294, column: 48, scope: !708)
!723 = !DILocation(line: 294, column: 52, scope: !708)
!724 = !DILocation(line: 294, column: 3, scope: !708)
!725 = !DILocation(line: 298, column: 2, scope: !398)
!726 = !DILocation(line: 298, column: 9, scope: !398)
!727 = !DILocation(line: 298, column: 24, scope: !398)
!728 = !DILocation(line: 300, column: 2, scope: !398)
!729 = !DILocation(line: 301, column: 1, scope: !398)
!730 = !DILocalVariable(name: "mf", arg: 1, scope: !409, file: !123, line: 253, type: !412)
!731 = !DILocation(line: 253, column: 28, scope: !409)
!732 = !DILocation(line: 255, column: 9, scope: !409)
!733 = !DILocation(line: 255, column: 13, scope: !409)
!734 = !DILocation(line: 255, column: 24, scope: !409)
!735 = !DILocation(line: 255, column: 28, scope: !409)
!736 = !DILocation(line: 255, column: 22, scope: !409)
!737 = !DILocation(line: 255, column: 2, scope: !409)
!738 = !DILocalVariable(name: "rc", arg: 1, scope: !414, file: !19, line: 151, type: !405)
!739 = !DILocation(line: 151, column: 31, scope: !414)
!740 = !DILocalVariable(name: "out", arg: 2, scope: !414, file: !19, line: 152, type: !223)
!741 = !DILocation(line: 152, column: 12, scope: !414)
!742 = !DILocalVariable(name: "out_pos", arg: 3, scope: !414, file: !19, line: 152, type: !256)
!743 = !DILocation(line: 152, column: 25, scope: !414)
!744 = !DILocalVariable(name: "out_size", arg: 4, scope: !414, file: !19, line: 152, type: !34)
!745 = !DILocation(line: 152, column: 41, scope: !414)
!746 = !DILocation(line: 154, column: 2, scope: !414)
!747 = !DILocation(line: 154, column: 2, scope: !748)
!748 = !DILexicalBlockFile(scope: !414, file: !19, discriminator: 1)
!749 = !DILocation(line: 154, column: 2, scope: !750)
!750 = !DILexicalBlockFile(scope: !414, file: !19, discriminator: 2)
!751 = !DILocation(line: 154, column: 2, scope: !752)
!752 = !DILexicalBlockFile(scope: !414, file: !19, discriminator: 3)
!753 = !DILocation(line: 156, column: 2, scope: !414)
!754 = !DILocation(line: 156, column: 9, scope: !748)
!755 = !DILocation(line: 156, column: 13, scope: !748)
!756 = !DILocation(line: 156, column: 19, scope: !748)
!757 = !DILocation(line: 156, column: 23, scope: !748)
!758 = !DILocation(line: 156, column: 17, scope: !748)
!759 = !DILocation(line: 156, column: 2, scope: !748)
!760 = !DILocation(line: 158, column: 7, scope: !761)
!761 = distinct !DILexicalBlock(scope: !762, file: !19, line: 158, column: 7)
!762 = distinct !DILexicalBlock(scope: !414, file: !19, line: 156, column: 30)
!763 = !DILocation(line: 158, column: 11, scope: !761)
!764 = !DILocation(line: 158, column: 17, scope: !761)
!765 = !DILocation(line: 158, column: 7, scope: !762)
!766 = !DILocation(line: 159, column: 21, scope: !767)
!767 = distinct !DILexicalBlock(scope: !768, file: !19, line: 159, column: 8)
!768 = distinct !DILexicalBlock(scope: !761, file: !19, line: 158, column: 33)
!769 = !DILocation(line: 159, column: 25, scope: !767)
!770 = !DILocation(line: 159, column: 30, scope: !767)
!771 = !DILocation(line: 159, column: 39, scope: !767)
!772 = !DILocation(line: 159, column: 8, scope: !767)
!773 = !DILocation(line: 159, column: 8, scope: !768)
!774 = !DILocation(line: 160, column: 5, scope: !767)
!775 = !DILocation(line: 162, column: 4, scope: !768)
!776 = !DILocation(line: 162, column: 8, scope: !768)
!777 = !DILocation(line: 162, column: 14, scope: !768)
!778 = !DILocation(line: 163, column: 3, scope: !768)
!779 = !DILocation(line: 166, column: 23, scope: !762)
!780 = !DILocation(line: 166, column: 27, scope: !762)
!781 = !DILocation(line: 166, column: 11, scope: !762)
!782 = !DILocation(line: 166, column: 15, scope: !762)
!783 = !DILocation(line: 166, column: 3, scope: !762)
!784 = !DILocalVariable(name: "prob", scope: !785, file: !19, line: 168, type: !44)
!785 = distinct !DILexicalBlock(scope: !786, file: !19, line: 167, column: 18)
!786 = distinct !DILexicalBlock(scope: !762, file: !19, line: 166, column: 33)
!787 = !DILocation(line: 168, column: 16, scope: !785)
!788 = !DILocation(line: 168, column: 34, scope: !785)
!789 = !DILocation(line: 168, column: 38, scope: !785)
!790 = !DILocation(line: 168, column: 24, scope: !785)
!791 = !DILocation(line: 168, column: 28, scope: !785)
!792 = !DILocation(line: 168, column: 23, scope: !785)
!793 = !DILocation(line: 169, column: 17, scope: !785)
!794 = !DILocation(line: 169, column: 21, scope: !785)
!795 = !DILocation(line: 169, column: 27, scope: !785)
!796 = !DILocation(line: 170, column: 8, scope: !785)
!797 = !DILocation(line: 170, column: 6, scope: !785)
!798 = !DILocation(line: 169, column: 4, scope: !785)
!799 = !DILocation(line: 169, column: 8, scope: !785)
!800 = !DILocation(line: 169, column: 14, scope: !785)
!801 = !DILocation(line: 171, column: 34, scope: !785)
!802 = !DILocation(line: 171, column: 32, scope: !785)
!803 = !DILocation(line: 171, column: 40, scope: !785)
!804 = !DILocation(line: 171, column: 9, scope: !785)
!805 = !DILocation(line: 172, column: 26, scope: !785)
!806 = !DILocation(line: 172, column: 15, scope: !785)
!807 = !DILocation(line: 172, column: 19, scope: !785)
!808 = !DILocation(line: 172, column: 5, scope: !785)
!809 = !DILocation(line: 172, column: 9, scope: !785)
!810 = !DILocation(line: 172, column: 24, scope: !785)
!811 = !DILocation(line: 173, column: 4, scope: !785)
!812 = !DILocalVariable(name: "prob", scope: !813, file: !19, line: 177, type: !44)
!813 = distinct !DILexicalBlock(scope: !786, file: !19, line: 176, column: 18)
!814 = !DILocation(line: 177, column: 16, scope: !813)
!815 = !DILocation(line: 177, column: 34, scope: !813)
!816 = !DILocation(line: 177, column: 38, scope: !813)
!817 = !DILocation(line: 177, column: 24, scope: !813)
!818 = !DILocation(line: 177, column: 28, scope: !813)
!819 = !DILocation(line: 177, column: 23, scope: !813)
!820 = !DILocalVariable(name: "bound", scope: !813, file: !19, line: 178, type: !433)
!821 = !DILocation(line: 178, column: 19, scope: !813)
!822 = !DILocation(line: 178, column: 27, scope: !813)
!823 = !DILocation(line: 178, column: 35, scope: !813)
!824 = !DILocation(line: 178, column: 39, scope: !813)
!825 = !DILocation(line: 179, column: 6, scope: !813)
!826 = !DILocation(line: 178, column: 32, scope: !813)
!827 = !DILocation(line: 180, column: 15, scope: !813)
!828 = !DILocation(line: 180, column: 4, scope: !813)
!829 = !DILocation(line: 180, column: 8, scope: !813)
!830 = !DILocation(line: 180, column: 12, scope: !813)
!831 = !DILocation(line: 181, column: 17, scope: !813)
!832 = !DILocation(line: 181, column: 4, scope: !813)
!833 = !DILocation(line: 181, column: 8, scope: !813)
!834 = !DILocation(line: 181, column: 14, scope: !813)
!835 = !DILocation(line: 182, column: 12, scope: !813)
!836 = !DILocation(line: 182, column: 17, scope: !813)
!837 = !DILocation(line: 182, column: 9, scope: !813)
!838 = !DILocation(line: 183, column: 26, scope: !813)
!839 = !DILocation(line: 183, column: 15, scope: !813)
!840 = !DILocation(line: 183, column: 19, scope: !813)
!841 = !DILocation(line: 183, column: 5, scope: !813)
!842 = !DILocation(line: 183, column: 9, scope: !813)
!843 = !DILocation(line: 183, column: 24, scope: !813)
!844 = !DILocation(line: 184, column: 4, scope: !813)
!845 = !DILocation(line: 188, column: 4, scope: !786)
!846 = !DILocation(line: 188, column: 8, scope: !786)
!847 = !DILocation(line: 188, column: 14, scope: !786)
!848 = !DILocation(line: 189, column: 4, scope: !786)
!849 = !DILocation(line: 192, column: 4, scope: !786)
!850 = !DILocation(line: 192, column: 8, scope: !786)
!851 = !DILocation(line: 192, column: 14, scope: !786)
!852 = !DILocation(line: 193, column: 15, scope: !786)
!853 = !DILocation(line: 193, column: 19, scope: !786)
!854 = !DILocation(line: 193, column: 4, scope: !786)
!855 = !DILocation(line: 193, column: 8, scope: !786)
!856 = !DILocation(line: 193, column: 12, scope: !786)
!857 = !DILocation(line: 194, column: 4, scope: !786)
!858 = !DILocation(line: 198, column: 4, scope: !786)
!859 = !DILocation(line: 198, column: 8, scope: !786)
!860 = !DILocation(line: 198, column: 14, scope: !786)
!861 = !DILocation(line: 201, column: 4, scope: !786)
!862 = !DILocation(line: 202, column: 22, scope: !863)
!863 = distinct !DILexicalBlock(scope: !864, file: !19, line: 202, column: 9)
!864 = distinct !DILexicalBlock(scope: !786, file: !19, line: 201, column: 7)
!865 = !DILocation(line: 202, column: 26, scope: !863)
!866 = !DILocation(line: 202, column: 31, scope: !863)
!867 = !DILocation(line: 202, column: 40, scope: !863)
!868 = !DILocation(line: 202, column: 9, scope: !863)
!869 = !DILocation(line: 202, column: 9, scope: !864)
!870 = !DILocation(line: 203, column: 6, scope: !863)
!871 = !DILocation(line: 204, column: 4, scope: !864)
!872 = !DILocation(line: 204, column: 15, scope: !873)
!873 = !DILexicalBlockFile(scope: !786, file: !19, discriminator: 1)
!874 = !DILocation(line: 204, column: 19, scope: !873)
!875 = !DILocation(line: 204, column: 13, scope: !873)
!876 = !DILocation(line: 204, column: 25, scope: !873)
!877 = !DILocation(line: 204, column: 29, scope: !873)
!878 = !DILocation(line: 204, column: 23, scope: !873)
!879 = !DILocation(line: 204, column: 4, scope: !873)
!880 = !DILocation(line: 208, column: 13, scope: !786)
!881 = !DILocation(line: 208, column: 4, scope: !786)
!882 = !DILocation(line: 209, column: 4, scope: !786)
!883 = !DILocation(line: 212, column: 4, scope: !786)
!884 = !DILocation(line: 216, column: 5, scope: !762)
!885 = !DILocation(line: 216, column: 9, scope: !762)
!886 = !DILocation(line: 216, column: 3, scope: !762)
!887 = !DILocation(line: 156, column: 2, scope: !750)
!888 = !DILocation(line: 219, column: 2, scope: !414)
!889 = !DILocation(line: 219, column: 6, scope: !414)
!890 = !DILocation(line: 219, column: 12, scope: !414)
!891 = !DILocation(line: 220, column: 2, scope: !414)
!892 = !DILocation(line: 220, column: 6, scope: !414)
!893 = !DILocation(line: 220, column: 10, scope: !414)
!894 = !DILocation(line: 222, column: 2, scope: !414)
!895 = !DILocation(line: 223, column: 1, scope: !414)
!896 = !DILocalVariable(name: "rc", arg: 1, scope: !418, file: !19, line: 227, type: !421)
!897 = !DILocation(line: 227, column: 38, scope: !418)
!898 = !DILocation(line: 229, column: 9, scope: !418)
!899 = !DILocation(line: 229, column: 13, scope: !418)
!900 = !DILocation(line: 229, column: 24, scope: !418)
!901 = !DILocation(line: 229, column: 28, scope: !418)
!902 = !DILocation(line: 229, column: 2, scope: !418)
!903 = !DILocalVariable(name: "coder", arg: 1, scope: !423, file: !1, line: 243, type: !106)
!904 = !DILocation(line: 243, column: 27, scope: !423)
!905 = !DILocalVariable(name: "mf", arg: 2, scope: !423, file: !1, line: 243, type: !218)
!906 = !DILocation(line: 243, column: 43, scope: !423)
!907 = !DILocalVariable(name: "back", arg: 3, scope: !423, file: !1, line: 244, type: !28)
!908 = !DILocation(line: 244, column: 12, scope: !423)
!909 = !DILocalVariable(name: "len", arg: 4, scope: !423, file: !1, line: 244, type: !28)
!910 = !DILocation(line: 244, column: 27, scope: !423)
!911 = !DILocalVariable(name: "position", arg: 5, scope: !423, file: !1, line: 244, type: !28)
!912 = !DILocation(line: 244, column: 41, scope: !423)
!913 = !DILocalVariable(name: "pos_state", scope: !423, file: !1, line: 246, type: !433)
!914 = !DILocation(line: 246, column: 17, scope: !423)
!915 = !DILocation(line: 246, column: 29, scope: !423)
!916 = !DILocation(line: 246, column: 40, scope: !423)
!917 = !DILocation(line: 246, column: 47, scope: !423)
!918 = !DILocation(line: 246, column: 38, scope: !423)
!919 = !DILocation(line: 248, column: 6, scope: !920)
!920 = distinct !DILexicalBlock(scope: !423, file: !1, line: 248, column: 6)
!921 = !DILocation(line: 248, column: 11, scope: !920)
!922 = !DILocation(line: 248, column: 6, scope: !423)
!923 = !DILocation(line: 250, column: 3, scope: !924)
!924 = distinct !DILexicalBlock(scope: !920, file: !1, line: 248, column: 26)
!925 = !DILocation(line: 250, column: 3, scope: !926)
!926 = !DILexicalBlockFile(scope: !924, file: !1, discriminator: 1)
!927 = !DILocation(line: 250, column: 3, scope: !928)
!928 = !DILexicalBlockFile(scope: !924, file: !1, discriminator: 2)
!929 = !DILocation(line: 250, column: 3, scope: !930)
!930 = !DILexicalBlockFile(scope: !924, file: !1, discriminator: 3)
!931 = !DILocation(line: 251, column: 11, scope: !924)
!932 = !DILocation(line: 251, column: 18, scope: !924)
!933 = !DILocation(line: 252, column: 36, scope: !924)
!934 = !DILocation(line: 252, column: 6, scope: !924)
!935 = !DILocation(line: 252, column: 22, scope: !924)
!936 = !DILocation(line: 252, column: 29, scope: !924)
!937 = !DILocation(line: 252, column: 13, scope: !924)
!938 = !DILocation(line: 251, column: 3, scope: !924)
!939 = !DILocation(line: 253, column: 11, scope: !924)
!940 = !DILocation(line: 253, column: 18, scope: !924)
!941 = !DILocation(line: 253, column: 22, scope: !924)
!942 = !DILocation(line: 253, column: 3, scope: !924)
!943 = !DILocation(line: 254, column: 2, scope: !924)
!944 = !DILocation(line: 256, column: 11, scope: !945)
!945 = distinct !DILexicalBlock(scope: !920, file: !1, line: 254, column: 9)
!946 = !DILocation(line: 256, column: 18, scope: !945)
!947 = !DILocation(line: 257, column: 35, scope: !945)
!948 = !DILocation(line: 257, column: 5, scope: !945)
!949 = !DILocation(line: 257, column: 21, scope: !945)
!950 = !DILocation(line: 257, column: 28, scope: !945)
!951 = !DILocation(line: 257, column: 12, scope: !945)
!952 = !DILocation(line: 256, column: 3, scope: !945)
!953 = !DILocation(line: 259, column: 7, scope: !954)
!954 = distinct !DILexicalBlock(scope: !945, file: !1, line: 259, column: 7)
!955 = !DILocation(line: 259, column: 12, scope: !954)
!956 = !DILocation(line: 259, column: 7, scope: !945)
!957 = !DILocation(line: 262, column: 12, scope: !958)
!958 = distinct !DILexicalBlock(scope: !954, file: !1, line: 259, column: 29)
!959 = !DILocation(line: 262, column: 19, scope: !958)
!960 = !DILocation(line: 262, column: 38, scope: !958)
!961 = !DILocation(line: 262, column: 45, scope: !958)
!962 = !DILocation(line: 262, column: 24, scope: !958)
!963 = !DILocation(line: 262, column: 31, scope: !958)
!964 = !DILocation(line: 262, column: 4, scope: !958)
!965 = !DILocation(line: 263, column: 14, scope: !958)
!966 = !DILocation(line: 263, column: 21, scope: !958)
!967 = !DILocation(line: 263, column: 32, scope: !958)
!968 = !DILocation(line: 263, column: 38, scope: !958)
!969 = !DILocation(line: 263, column: 4, scope: !958)
!970 = !DILocation(line: 264, column: 3, scope: !958)
!971 = !DILocation(line: 266, column: 12, scope: !972)
!972 = distinct !DILexicalBlock(scope: !954, file: !1, line: 264, column: 10)
!973 = !DILocation(line: 266, column: 19, scope: !972)
!974 = !DILocation(line: 266, column: 38, scope: !972)
!975 = !DILocation(line: 266, column: 45, scope: !972)
!976 = !DILocation(line: 266, column: 24, scope: !972)
!977 = !DILocation(line: 266, column: 31, scope: !972)
!978 = !DILocation(line: 266, column: 4, scope: !972)
!979 = !DILocation(line: 267, column: 10, scope: !972)
!980 = !DILocation(line: 267, column: 17, scope: !972)
!981 = !DILocation(line: 267, column: 28, scope: !972)
!982 = !DILocation(line: 267, column: 33, scope: !972)
!983 = !DILocation(line: 267, column: 50, scope: !972)
!984 = !DILocation(line: 267, column: 4, scope: !972)
!985 = !DILocation(line: 271, column: 2, scope: !423)
!986 = !DILocation(line: 271, column: 2, scope: !987)
!987 = !DILexicalBlockFile(scope: !423, file: !1, discriminator: 1)
!988 = !DILocation(line: 271, column: 2, scope: !989)
!989 = !DILexicalBlockFile(scope: !423, file: !1, discriminator: 2)
!990 = !DILocation(line: 271, column: 2, scope: !991)
!991 = !DILexicalBlockFile(scope: !423, file: !1, discriminator: 3)
!992 = !DILocation(line: 272, column: 20, scope: !423)
!993 = !DILocation(line: 272, column: 2, scope: !423)
!994 = !DILocation(line: 272, column: 6, scope: !423)
!995 = !DILocation(line: 272, column: 17, scope: !423)
!996 = !DILocation(line: 273, column: 1, scope: !423)
!997 = !DILocalVariable(name: "coder", arg: 1, scope: !465, file: !1, line: 305, type: !106)
!998 = !DILocation(line: 305, column: 25, scope: !465)
!999 = !DILocalVariable(name: "position", arg: 2, scope: !465, file: !1, line: 305, type: !28)
!1000 = !DILocation(line: 305, column: 41, scope: !465)
!1001 = !DILocalVariable(name: "pos_state", scope: !465, file: !1, line: 307, type: !433)
!1002 = !DILocation(line: 307, column: 17, scope: !465)
!1003 = !DILocation(line: 307, column: 29, scope: !465)
!1004 = !DILocation(line: 307, column: 40, scope: !465)
!1005 = !DILocation(line: 307, column: 47, scope: !465)
!1006 = !DILocation(line: 307, column: 38, scope: !465)
!1007 = !DILocation(line: 308, column: 10, scope: !465)
!1008 = !DILocation(line: 308, column: 17, scope: !465)
!1009 = !DILocation(line: 308, column: 52, scope: !465)
!1010 = !DILocation(line: 308, column: 22, scope: !465)
!1011 = !DILocation(line: 308, column: 38, scope: !465)
!1012 = !DILocation(line: 308, column: 45, scope: !465)
!1013 = !DILocation(line: 308, column: 29, scope: !465)
!1014 = !DILocation(line: 308, column: 2, scope: !465)
!1015 = !DILocation(line: 309, column: 10, scope: !465)
!1016 = !DILocation(line: 309, column: 17, scope: !465)
!1017 = !DILocation(line: 309, column: 36, scope: !465)
!1018 = !DILocation(line: 309, column: 43, scope: !465)
!1019 = !DILocation(line: 309, column: 22, scope: !465)
!1020 = !DILocation(line: 309, column: 29, scope: !465)
!1021 = !DILocation(line: 309, column: 2, scope: !465)
!1022 = !DILocation(line: 310, column: 8, scope: !465)
!1023 = !DILocation(line: 310, column: 15, scope: !465)
!1024 = !DILocation(line: 310, column: 2, scope: !465)
!1025 = !DILocation(line: 311, column: 1, scope: !465)
!1026 = !DILocalVariable(name: "rc", arg: 1, scope: !468, file: !19, line: 116, type: !405)
!1027 = !DILocation(line: 116, column: 30, scope: !468)
!1028 = !DILocalVariable(name: "i", scope: !468, file: !19, line: 118, type: !34)
!1029 = !DILocation(line: 118, column: 9, scope: !468)
!1030 = !DILocation(line: 119, column: 9, scope: !1031)
!1031 = distinct !DILexicalBlock(scope: !468, file: !19, line: 119, column: 2)
!1032 = !DILocation(line: 119, column: 7, scope: !1031)
!1033 = !DILocation(line: 119, column: 14, scope: !1034)
!1034 = !DILexicalBlockFile(scope: !1035, file: !19, discriminator: 1)
!1035 = distinct !DILexicalBlock(scope: !1031, file: !19, line: 119, column: 2)
!1036 = !DILocation(line: 119, column: 16, scope: !1034)
!1037 = !DILocation(line: 119, column: 2, scope: !1034)
!1038 = !DILocation(line: 120, column: 15, scope: !1035)
!1039 = !DILocation(line: 120, column: 19, scope: !1035)
!1040 = !DILocation(line: 120, column: 24, scope: !1035)
!1041 = !DILocation(line: 120, column: 3, scope: !1035)
!1042 = !DILocation(line: 120, column: 7, scope: !1035)
!1043 = !DILocation(line: 120, column: 28, scope: !1035)
!1044 = !DILocation(line: 119, column: 21, scope: !1045)
!1045 = !DILexicalBlockFile(scope: !1035, file: !19, discriminator: 2)
!1046 = !DILocation(line: 119, column: 2, scope: !1045)
!1047 = !DILocation(line: 121, column: 1, scope: !468)
!1048 = !DILocalVariable(name: "coder", arg: 1, scope: !258, file: !1, line: 490, type: !106)
!1049 = !DILocation(line: 490, column: 37, scope: !258)
!1050 = !DILocalVariable(name: "options", arg: 2, scope: !258, file: !1, line: 490, type: !261)
!1051 = !DILocation(line: 490, column: 69, scope: !258)
!1052 = !DILocalVariable(name: "i", scope: !258, file: !1, line: 492, type: !34)
!1053 = !DILocation(line: 492, column: 9, scope: !258)
!1054 = !DILocalVariable(name: "j", scope: !258, file: !1, line: 492, type: !34)
!1055 = !DILocation(line: 492, column: 12, scope: !258)
!1056 = !DILocation(line: 494, column: 24, scope: !1057)
!1057 = distinct !DILexicalBlock(scope: !258, file: !1, line: 494, column: 6)
!1058 = !DILocation(line: 494, column: 7, scope: !1057)
!1059 = !DILocation(line: 494, column: 6, scope: !258)
!1060 = !DILocation(line: 495, column: 3, scope: !1057)
!1061 = !DILocation(line: 497, column: 27, scope: !258)
!1062 = !DILocation(line: 497, column: 36, scope: !258)
!1063 = !DILocation(line: 497, column: 24, scope: !258)
!1064 = !DILocation(line: 497, column: 40, scope: !258)
!1065 = !DILocation(line: 497, column: 2, scope: !258)
!1066 = !DILocation(line: 497, column: 9, scope: !258)
!1067 = !DILocation(line: 497, column: 18, scope: !258)
!1068 = !DILocation(line: 498, column: 32, scope: !258)
!1069 = !DILocation(line: 498, column: 41, scope: !258)
!1070 = !DILocation(line: 498, column: 2, scope: !258)
!1071 = !DILocation(line: 498, column: 9, scope: !258)
!1072 = !DILocation(line: 498, column: 30, scope: !258)
!1073 = !DILocation(line: 499, column: 35, scope: !258)
!1074 = !DILocation(line: 499, column: 44, scope: !258)
!1075 = !DILocation(line: 499, column: 32, scope: !258)
!1076 = !DILocation(line: 499, column: 48, scope: !258)
!1077 = !DILocation(line: 499, column: 2, scope: !258)
!1078 = !DILocation(line: 499, column: 9, scope: !258)
!1079 = !DILocation(line: 499, column: 26, scope: !258)
!1080 = !DILocation(line: 502, column: 12, scope: !258)
!1081 = !DILocation(line: 502, column: 19, scope: !258)
!1082 = !DILocation(line: 502, column: 2, scope: !258)
!1083 = !DILocation(line: 505, column: 2, scope: !258)
!1084 = !DILocation(line: 505, column: 9, scope: !258)
!1085 = !DILocation(line: 505, column: 15, scope: !258)
!1086 = !DILocation(line: 506, column: 9, scope: !1087)
!1087 = distinct !DILexicalBlock(scope: !258, file: !1, line: 506, column: 2)
!1088 = !DILocation(line: 506, column: 7, scope: !1087)
!1089 = !DILocation(line: 506, column: 14, scope: !1090)
!1090 = !DILexicalBlockFile(scope: !1091, file: !1, discriminator: 1)
!1091 = distinct !DILexicalBlock(scope: !1087, file: !1, line: 506, column: 2)
!1092 = !DILocation(line: 506, column: 16, scope: !1090)
!1093 = !DILocation(line: 506, column: 2, scope: !1090)
!1094 = !DILocation(line: 507, column: 15, scope: !1091)
!1095 = !DILocation(line: 507, column: 3, scope: !1091)
!1096 = !DILocation(line: 507, column: 10, scope: !1091)
!1097 = !DILocation(line: 507, column: 18, scope: !1091)
!1098 = !DILocation(line: 506, column: 33, scope: !1099)
!1099 = !DILexicalBlockFile(scope: !1091, file: !1, discriminator: 2)
!1100 = !DILocation(line: 506, column: 2, scope: !1099)
!1101 = !DILocation(line: 509, column: 15, scope: !258)
!1102 = !DILocation(line: 509, column: 22, scope: !258)
!1103 = !DILocation(line: 509, column: 31, scope: !258)
!1104 = !DILocation(line: 509, column: 40, scope: !258)
!1105 = !DILocation(line: 509, column: 44, scope: !258)
!1106 = !DILocation(line: 509, column: 53, scope: !258)
!1107 = !DILocation(line: 509, column: 2, scope: !258)
!1108 = !DILocation(line: 512, column: 9, scope: !1109)
!1109 = distinct !DILexicalBlock(scope: !258, file: !1, line: 512, column: 2)
!1110 = !DILocation(line: 512, column: 7, scope: !1109)
!1111 = !DILocation(line: 512, column: 14, scope: !1112)
!1112 = !DILexicalBlockFile(scope: !1113, file: !1, discriminator: 1)
!1113 = distinct !DILexicalBlock(scope: !1109, file: !1, line: 512, column: 2)
!1114 = !DILocation(line: 512, column: 16, scope: !1112)
!1115 = !DILocation(line: 512, column: 2, scope: !1112)
!1116 = !DILocation(line: 513, column: 10, scope: !1117)
!1117 = distinct !DILexicalBlock(scope: !1118, file: !1, line: 513, column: 3)
!1118 = distinct !DILexicalBlock(scope: !1113, file: !1, line: 512, column: 31)
!1119 = !DILocation(line: 513, column: 8, scope: !1117)
!1120 = !DILocation(line: 513, column: 15, scope: !1121)
!1121 = !DILexicalBlockFile(scope: !1122, file: !1, discriminator: 1)
!1122 = distinct !DILexicalBlock(scope: !1117, file: !1, line: 513, column: 3)
!1123 = !DILocation(line: 513, column: 20, scope: !1121)
!1124 = !DILocation(line: 513, column: 27, scope: !1121)
!1125 = !DILocation(line: 513, column: 17, scope: !1121)
!1126 = !DILocation(line: 513, column: 3, scope: !1121)
!1127 = !DILocation(line: 514, column: 4, scope: !1128)
!1128 = distinct !DILexicalBlock(scope: !1122, file: !1, line: 513, column: 42)
!1129 = !DILocation(line: 515, column: 4, scope: !1128)
!1130 = !DILocation(line: 516, column: 3, scope: !1128)
!1131 = !DILocation(line: 513, column: 37, scope: !1132)
!1132 = !DILexicalBlockFile(scope: !1122, file: !1, discriminator: 2)
!1133 = !DILocation(line: 513, column: 3, scope: !1132)
!1134 = !DILocation(line: 518, column: 3, scope: !1118)
!1135 = !DILocation(line: 519, column: 3, scope: !1118)
!1136 = !DILocation(line: 520, column: 3, scope: !1118)
!1137 = !DILocation(line: 521, column: 3, scope: !1118)
!1138 = !DILocation(line: 522, column: 2, scope: !1118)
!1139 = !DILocation(line: 512, column: 26, scope: !1140)
!1140 = !DILexicalBlockFile(scope: !1113, file: !1, discriminator: 2)
!1141 = !DILocation(line: 512, column: 2, scope: !1140)
!1142 = !DILocation(line: 524, column: 9, scope: !1143)
!1143 = distinct !DILexicalBlock(scope: !258, file: !1, line: 524, column: 2)
!1144 = !DILocation(line: 524, column: 7, scope: !1143)
!1145 = !DILocation(line: 524, column: 14, scope: !1146)
!1146 = !DILexicalBlockFile(scope: !1147, file: !1, discriminator: 1)
!1147 = distinct !DILexicalBlock(scope: !1143, file: !1, line: 524, column: 2)
!1148 = !DILocation(line: 524, column: 16, scope: !1146)
!1149 = !DILocation(line: 524, column: 2, scope: !1146)
!1150 = !DILocation(line: 525, column: 3, scope: !1147)
!1151 = !DILocation(line: 524, column: 56, scope: !1152)
!1152 = !DILexicalBlockFile(scope: !1147, file: !1, discriminator: 2)
!1153 = !DILocation(line: 524, column: 2, scope: !1152)
!1154 = !DILocation(line: 528, column: 9, scope: !1155)
!1155 = distinct !DILexicalBlock(scope: !258, file: !1, line: 528, column: 2)
!1156 = !DILocation(line: 528, column: 7, scope: !1155)
!1157 = !DILocation(line: 528, column: 14, scope: !1158)
!1158 = !DILexicalBlockFile(scope: !1159, file: !1, discriminator: 1)
!1159 = distinct !DILexicalBlock(scope: !1155, file: !1, line: 528, column: 2)
!1160 = !DILocation(line: 528, column: 16, scope: !1158)
!1161 = !DILocation(line: 528, column: 2, scope: !1158)
!1162 = !DILocation(line: 529, column: 3, scope: !1159)
!1163 = !DILocalVariable(name: "bt_i", scope: !1164, file: !1, line: 529, type: !28)
!1164 = distinct !DILexicalBlock(scope: !1159, file: !1, line: 529, column: 3)
!1165 = !DILocation(line: 529, column: 3, scope: !1164)
!1166 = !DILocation(line: 529, column: 3, scope: !1167)
!1167 = !DILexicalBlockFile(scope: !1168, file: !1, discriminator: 1)
!1168 = distinct !DILexicalBlock(scope: !1164, file: !1, line: 529, column: 3)
!1169 = !DILocation(line: 529, column: 3, scope: !1170)
!1170 = !DILexicalBlockFile(scope: !1171, file: !1, discriminator: 2)
!1171 = distinct !DILexicalBlock(scope: !1168, file: !1, line: 529, column: 3)
!1172 = !DILocation(line: 529, column: 3, scope: !1173)
!1173 = !DILexicalBlockFile(scope: !1171, file: !1, discriminator: 3)
!1174 = !DILocation(line: 529, column: 3, scope: !1175)
!1175 = !DILexicalBlockFile(scope: !1171, file: !1, discriminator: 4)
!1176 = !DILocation(line: 529, column: 3, scope: !1177)
!1177 = !DILexicalBlockFile(scope: !1164, file: !1, discriminator: 5)
!1178 = !DILocation(line: 529, column: 3, scope: !1179)
!1179 = !DILexicalBlockFile(scope: !1164, file: !1, discriminator: 6)
!1180 = !DILocation(line: 528, column: 37, scope: !1181)
!1181 = !DILexicalBlockFile(scope: !1159, file: !1, discriminator: 2)
!1182 = !DILocation(line: 528, column: 2, scope: !1181)
!1183 = !DILocation(line: 531, column: 2, scope: !258)
!1184 = !DILocalVariable(name: "bt_i", scope: !1185, file: !1, line: 531, type: !28)
!1185 = distinct !DILexicalBlock(scope: !258, file: !1, line: 531, column: 2)
!1186 = !DILocation(line: 531, column: 2, scope: !1185)
!1187 = !DILocation(line: 531, column: 2, scope: !1188)
!1188 = !DILexicalBlockFile(scope: !1189, file: !1, discriminator: 1)
!1189 = distinct !DILexicalBlock(scope: !1185, file: !1, line: 531, column: 2)
!1190 = !DILocation(line: 531, column: 2, scope: !1191)
!1191 = !DILexicalBlockFile(scope: !1192, file: !1, discriminator: 2)
!1192 = distinct !DILexicalBlock(scope: !1189, file: !1, line: 531, column: 2)
!1193 = !DILocation(line: 531, column: 2, scope: !1194)
!1194 = !DILexicalBlockFile(scope: !1192, file: !1, discriminator: 3)
!1195 = !DILocation(line: 531, column: 2, scope: !1196)
!1196 = !DILexicalBlockFile(scope: !1192, file: !1, discriminator: 4)
!1197 = !DILocation(line: 531, column: 2, scope: !1198)
!1198 = !DILexicalBlockFile(scope: !1185, file: !1, discriminator: 5)
!1199 = !DILocation(line: 534, column: 24, scope: !258)
!1200 = !DILocation(line: 534, column: 31, scope: !258)
!1201 = !DILocation(line: 535, column: 10, scope: !258)
!1202 = !DILocation(line: 535, column: 19, scope: !258)
!1203 = !DILocation(line: 535, column: 7, scope: !258)
!1204 = !DILocation(line: 535, column: 23, scope: !258)
!1205 = !DILocation(line: 535, column: 30, scope: !258)
!1206 = !DILocation(line: 534, column: 2, scope: !258)
!1207 = !DILocation(line: 537, column: 24, scope: !258)
!1208 = !DILocation(line: 537, column: 31, scope: !258)
!1209 = !DILocation(line: 538, column: 10, scope: !258)
!1210 = !DILocation(line: 538, column: 19, scope: !258)
!1211 = !DILocation(line: 538, column: 7, scope: !258)
!1212 = !DILocation(line: 538, column: 23, scope: !258)
!1213 = !DILocation(line: 538, column: 30, scope: !258)
!1214 = !DILocation(line: 537, column: 2, scope: !258)
!1215 = !DILocation(line: 553, column: 2, scope: !258)
!1216 = !DILocation(line: 553, column: 9, scope: !258)
!1217 = !DILocation(line: 553, column: 27, scope: !258)
!1218 = !DILocation(line: 554, column: 2, scope: !258)
!1219 = !DILocation(line: 554, column: 9, scope: !258)
!1220 = !DILocation(line: 554, column: 27, scope: !258)
!1221 = !DILocation(line: 556, column: 2, scope: !258)
!1222 = !DILocation(line: 556, column: 9, scope: !258)
!1223 = !DILocation(line: 556, column: 24, scope: !258)
!1224 = !DILocation(line: 557, column: 2, scope: !258)
!1225 = !DILocation(line: 557, column: 9, scope: !258)
!1226 = !DILocation(line: 557, column: 28, scope: !258)
!1227 = !DILocation(line: 559, column: 2, scope: !258)
!1228 = !DILocation(line: 560, column: 1, scope: !258)
!1229 = !DILocalVariable(name: "options", arg: 1, scope: !471, file: !1, line: 434, type: !261)
!1230 = !DILocation(line: 434, column: 43, scope: !471)
!1231 = !DILocation(line: 438, column: 25, scope: !471)
!1232 = !DILocation(line: 438, column: 9, scope: !471)
!1233 = !DILocation(line: 439, column: 4, scope: !471)
!1234 = !DILocation(line: 439, column: 7, scope: !1235)
!1235 = !DILexicalBlockFile(scope: !471, file: !1, discriminator: 1)
!1236 = !DILocation(line: 439, column: 16, scope: !1235)
!1237 = !DILocation(line: 439, column: 25, scope: !1235)
!1238 = !DILocation(line: 440, column: 4, scope: !471)
!1239 = !DILocation(line: 440, column: 7, scope: !1235)
!1240 = !DILocation(line: 440, column: 16, scope: !1235)
!1241 = !DILocation(line: 440, column: 25, scope: !1235)
!1242 = !DILocation(line: 441, column: 4, scope: !471)
!1243 = !DILocation(line: 441, column: 8, scope: !1235)
!1244 = !DILocation(line: 441, column: 17, scope: !1235)
!1245 = !DILocation(line: 441, column: 22, scope: !1235)
!1246 = !DILocation(line: 442, column: 5, scope: !471)
!1247 = !DILocation(line: 442, column: 8, scope: !1235)
!1248 = !DILocation(line: 442, column: 17, scope: !1235)
!1249 = !DILocation(line: 442, column: 22, scope: !1235)
!1250 = !DILocation(line: 442, column: 5, scope: !1235)
!1251 = !DILocation(line: 438, column: 2, scope: !1235)
!1252 = !DILocalVariable(name: "rc", arg: 1, scope: !474, file: !19, line: 55, type: !405)
!1253 = !DILocation(line: 55, column: 30, scope: !474)
!1254 = !DILocation(line: 57, column: 2, scope: !474)
!1255 = !DILocation(line: 57, column: 6, scope: !474)
!1256 = !DILocation(line: 57, column: 10, scope: !474)
!1257 = !DILocation(line: 58, column: 2, scope: !474)
!1258 = !DILocation(line: 58, column: 6, scope: !474)
!1259 = !DILocation(line: 58, column: 17, scope: !474)
!1260 = !DILocation(line: 59, column: 2, scope: !474)
!1261 = !DILocation(line: 59, column: 6, scope: !474)
!1262 = !DILocation(line: 59, column: 12, scope: !474)
!1263 = !DILocation(line: 60, column: 2, scope: !474)
!1264 = !DILocation(line: 60, column: 6, scope: !474)
!1265 = !DILocation(line: 60, column: 12, scope: !474)
!1266 = !DILocation(line: 61, column: 2, scope: !474)
!1267 = !DILocation(line: 61, column: 6, scope: !474)
!1268 = !DILocation(line: 61, column: 12, scope: !474)
!1269 = !DILocation(line: 62, column: 2, scope: !474)
!1270 = !DILocation(line: 62, column: 6, scope: !474)
!1271 = !DILocation(line: 62, column: 10, scope: !474)
!1272 = !DILocation(line: 63, column: 1, scope: !474)
!1273 = !DILocalVariable(name: "probs", arg: 1, scope: !475, file: !55, line: 129, type: !478)
!1274 = !DILocation(line: 129, column: 28, scope: !475)
!1275 = !DILocalVariable(name: "lc", arg: 2, scope: !475, file: !55, line: 130, type: !28)
!1276 = !DILocation(line: 130, column: 12, scope: !475)
!1277 = !DILocalVariable(name: "lp", arg: 3, scope: !475, file: !55, line: 130, type: !28)
!1278 = !DILocation(line: 130, column: 25, scope: !475)
!1279 = !DILocalVariable(name: "coders", scope: !475, file: !55, line: 132, type: !28)
!1280 = !DILocation(line: 132, column: 11, scope: !475)
!1281 = !DILocalVariable(name: "i", scope: !475, file: !55, line: 133, type: !28)
!1282 = !DILocation(line: 133, column: 11, scope: !475)
!1283 = !DILocalVariable(name: "j", scope: !475, file: !55, line: 133, type: !28)
!1284 = !DILocation(line: 133, column: 14, scope: !475)
!1285 = !DILocation(line: 135, column: 2, scope: !475)
!1286 = !DILocation(line: 135, column: 2, scope: !1287)
!1287 = !DILexicalBlockFile(scope: !475, file: !55, discriminator: 1)
!1288 = !DILocation(line: 135, column: 2, scope: !1289)
!1289 = !DILexicalBlockFile(scope: !475, file: !55, discriminator: 2)
!1290 = !DILocation(line: 135, column: 2, scope: !1291)
!1291 = !DILexicalBlockFile(scope: !475, file: !55, discriminator: 3)
!1292 = !DILocation(line: 137, column: 18, scope: !475)
!1293 = !DILocation(line: 137, column: 23, scope: !475)
!1294 = !DILocation(line: 137, column: 21, scope: !475)
!1295 = !DILocation(line: 137, column: 14, scope: !475)
!1296 = !DILocation(line: 137, column: 9, scope: !475)
!1297 = !DILocation(line: 139, column: 9, scope: !1298)
!1298 = distinct !DILexicalBlock(scope: !475, file: !55, line: 139, column: 2)
!1299 = !DILocation(line: 139, column: 7, scope: !1298)
!1300 = !DILocation(line: 139, column: 14, scope: !1301)
!1301 = !DILexicalBlockFile(scope: !1302, file: !55, discriminator: 1)
!1302 = distinct !DILexicalBlock(scope: !1298, file: !55, line: 139, column: 2)
!1303 = !DILocation(line: 139, column: 18, scope: !1301)
!1304 = !DILocation(line: 139, column: 16, scope: !1301)
!1305 = !DILocation(line: 139, column: 2, scope: !1301)
!1306 = !DILocation(line: 140, column: 10, scope: !1307)
!1307 = distinct !DILexicalBlock(scope: !1302, file: !55, line: 140, column: 3)
!1308 = !DILocation(line: 140, column: 8, scope: !1307)
!1309 = !DILocation(line: 140, column: 15, scope: !1310)
!1310 = !DILexicalBlockFile(scope: !1311, file: !55, discriminator: 1)
!1311 = distinct !DILexicalBlock(scope: !1307, file: !55, line: 140, column: 3)
!1312 = !DILocation(line: 140, column: 17, scope: !1310)
!1313 = !DILocation(line: 140, column: 3, scope: !1310)
!1314 = !DILocation(line: 141, column: 4, scope: !1311)
!1315 = !DILocation(line: 140, column: 39, scope: !1316)
!1316 = !DILexicalBlockFile(scope: !1311, file: !55, discriminator: 2)
!1317 = !DILocation(line: 140, column: 3, scope: !1316)
!1318 = !DILocation(line: 141, column: 4, scope: !1319)
!1319 = !DILexicalBlockFile(scope: !1307, file: !55, discriminator: 1)
!1320 = !DILocation(line: 139, column: 26, scope: !1321)
!1321 = !DILexicalBlockFile(scope: !1302, file: !55, discriminator: 2)
!1322 = !DILocation(line: 139, column: 2, scope: !1321)
!1323 = !DILocation(line: 143, column: 2, scope: !475)
!1324 = !DILocalVariable(name: "lencoder", arg: 1, scope: !481, file: !1, line: 465, type: !437)
!1325 = !DILocation(line: 465, column: 43, scope: !481)
!1326 = !DILocalVariable(name: "num_pos_states", arg: 2, scope: !481, file: !1, line: 466, type: !433)
!1327 = !DILocation(line: 466, column: 18, scope: !481)
!1328 = !DILocalVariable(name: "fast_mode", arg: 3, scope: !481, file: !1, line: 466, type: !438)
!1329 = !DILocation(line: 466, column: 45, scope: !481)
!1330 = !DILocalVariable(name: "pos_state", scope: !481, file: !1, line: 468, type: !34)
!1331 = !DILocation(line: 468, column: 9, scope: !481)
!1332 = !DILocation(line: 470, column: 2, scope: !481)
!1333 = !DILocation(line: 471, column: 2, scope: !481)
!1334 = !DILocation(line: 473, column: 17, scope: !1335)
!1335 = distinct !DILexicalBlock(scope: !481, file: !1, line: 473, column: 2)
!1336 = !DILocation(line: 473, column: 7, scope: !1335)
!1337 = !DILocation(line: 473, column: 22, scope: !1338)
!1338 = !DILexicalBlockFile(scope: !1339, file: !1, discriminator: 1)
!1339 = distinct !DILexicalBlock(scope: !1335, file: !1, line: 473, column: 2)
!1340 = !DILocation(line: 473, column: 34, scope: !1338)
!1341 = !DILocation(line: 473, column: 32, scope: !1338)
!1342 = !DILocation(line: 473, column: 2, scope: !1338)
!1343 = !DILocation(line: 474, column: 3, scope: !1344)
!1344 = distinct !DILexicalBlock(scope: !1339, file: !1, line: 473, column: 63)
!1345 = !DILocalVariable(name: "bt_i", scope: !1346, file: !1, line: 474, type: !28)
!1346 = distinct !DILexicalBlock(scope: !1344, file: !1, line: 474, column: 3)
!1347 = !DILocation(line: 474, column: 3, scope: !1346)
!1348 = !DILocation(line: 474, column: 3, scope: !1349)
!1349 = !DILexicalBlockFile(scope: !1350, file: !1, discriminator: 1)
!1350 = distinct !DILexicalBlock(scope: !1346, file: !1, line: 474, column: 3)
!1351 = !DILocation(line: 474, column: 3, scope: !1352)
!1352 = !DILexicalBlockFile(scope: !1353, file: !1, discriminator: 2)
!1353 = distinct !DILexicalBlock(scope: !1350, file: !1, line: 474, column: 3)
!1354 = !DILocation(line: 474, column: 3, scope: !1355)
!1355 = !DILexicalBlockFile(scope: !1353, file: !1, discriminator: 3)
!1356 = !DILocation(line: 474, column: 3, scope: !1357)
!1357 = !DILexicalBlockFile(scope: !1353, file: !1, discriminator: 4)
!1358 = !DILocation(line: 474, column: 3, scope: !1359)
!1359 = !DILexicalBlockFile(scope: !1346, file: !1, discriminator: 5)
!1360 = !DILocation(line: 475, column: 3, scope: !1344)
!1361 = !DILocalVariable(name: "bt_i", scope: !1362, file: !1, line: 475, type: !28)
!1362 = distinct !DILexicalBlock(scope: !1344, file: !1, line: 475, column: 3)
!1363 = !DILocation(line: 475, column: 3, scope: !1362)
!1364 = !DILocation(line: 475, column: 3, scope: !1365)
!1365 = !DILexicalBlockFile(scope: !1366, file: !1, discriminator: 1)
!1366 = distinct !DILexicalBlock(scope: !1362, file: !1, line: 475, column: 3)
!1367 = !DILocation(line: 475, column: 3, scope: !1368)
!1368 = !DILexicalBlockFile(scope: !1369, file: !1, discriminator: 2)
!1369 = distinct !DILexicalBlock(scope: !1366, file: !1, line: 475, column: 3)
!1370 = !DILocation(line: 475, column: 3, scope: !1371)
!1371 = !DILexicalBlockFile(scope: !1369, file: !1, discriminator: 3)
!1372 = !DILocation(line: 475, column: 3, scope: !1373)
!1373 = !DILexicalBlockFile(scope: !1369, file: !1, discriminator: 4)
!1374 = !DILocation(line: 475, column: 3, scope: !1375)
!1375 = !DILexicalBlockFile(scope: !1362, file: !1, discriminator: 5)
!1376 = !DILocation(line: 476, column: 2, scope: !1344)
!1377 = !DILocation(line: 473, column: 50, scope: !1378)
!1378 = !DILexicalBlockFile(scope: !1339, file: !1, discriminator: 2)
!1379 = !DILocation(line: 473, column: 2, scope: !1378)
!1380 = !DILocation(line: 478, column: 2, scope: !481)
!1381 = !DILocalVariable(name: "bt_i", scope: !1382, file: !1, line: 478, type: !28)
!1382 = distinct !DILexicalBlock(scope: !481, file: !1, line: 478, column: 2)
!1383 = !DILocation(line: 478, column: 2, scope: !1382)
!1384 = !DILocation(line: 478, column: 2, scope: !1385)
!1385 = !DILexicalBlockFile(scope: !1386, file: !1, discriminator: 1)
!1386 = distinct !DILexicalBlock(scope: !1382, file: !1, line: 478, column: 2)
!1387 = !DILocation(line: 478, column: 2, scope: !1388)
!1388 = !DILexicalBlockFile(scope: !1389, file: !1, discriminator: 2)
!1389 = distinct !DILexicalBlock(scope: !1386, file: !1, line: 478, column: 2)
!1390 = !DILocation(line: 478, column: 2, scope: !1391)
!1391 = !DILexicalBlockFile(scope: !1389, file: !1, discriminator: 3)
!1392 = !DILocation(line: 478, column: 2, scope: !1393)
!1393 = !DILexicalBlockFile(scope: !1389, file: !1, discriminator: 4)
!1394 = !DILocation(line: 478, column: 2, scope: !1395)
!1395 = !DILexicalBlockFile(scope: !1382, file: !1, discriminator: 5)
!1396 = !DILocation(line: 480, column: 7, scope: !1397)
!1397 = distinct !DILexicalBlock(scope: !481, file: !1, line: 480, column: 6)
!1398 = !DILocation(line: 480, column: 6, scope: !481)
!1399 = !DILocation(line: 481, column: 18, scope: !1400)
!1400 = distinct !DILexicalBlock(scope: !1397, file: !1, line: 481, column: 3)
!1401 = !DILocation(line: 481, column: 8, scope: !1400)
!1402 = !DILocation(line: 481, column: 23, scope: !1403)
!1403 = !DILexicalBlockFile(scope: !1404, file: !1, discriminator: 1)
!1404 = distinct !DILexicalBlock(scope: !1400, file: !1, line: 481, column: 3)
!1405 = !DILocation(line: 481, column: 35, scope: !1403)
!1406 = !DILocation(line: 481, column: 33, scope: !1403)
!1407 = !DILocation(line: 481, column: 3, scope: !1403)
!1408 = !DILocation(line: 483, column: 25, scope: !1404)
!1409 = !DILocation(line: 483, column: 35, scope: !1404)
!1410 = !DILocation(line: 483, column: 4, scope: !1404)
!1411 = !DILocation(line: 482, column: 5, scope: !1404)
!1412 = !DILocation(line: 481, column: 3, scope: !1413)
!1413 = !DILexicalBlockFile(scope: !1404, file: !1, discriminator: 2)
!1414 = !DILocation(line: 483, column: 44, scope: !1415)
!1415 = !DILexicalBlockFile(scope: !1400, file: !1, discriminator: 1)
!1416 = !DILocation(line: 485, column: 2, scope: !481)
!1417 = !DILocalVariable(name: "coder_ptr", arg: 1, scope: !295, file: !1, line: 564, type: !298)
!1418 = !DILocation(line: 564, column: 39, scope: !295)
!1419 = !DILocalVariable(name: "allocator", arg: 2, scope: !295, file: !1, line: 564, type: !299)
!1420 = !DILocation(line: 564, column: 66, scope: !295)
!1421 = !DILocalVariable(name: "options", arg: 3, scope: !295, file: !1, line: 565, type: !261)
!1422 = !DILocation(line: 565, column: 28, scope: !295)
!1423 = !DILocalVariable(name: "lz_options", arg: 4, scope: !295, file: !1, line: 565, type: !312)
!1424 = !DILocation(line: 565, column: 54, scope: !295)
!1425 = !DILocalVariable(name: "coder", scope: !295, file: !1, line: 567, type: !106)
!1426 = !DILocation(line: 567, column: 14, scope: !295)
!1427 = !DILocalVariable(name: "log_size", scope: !295, file: !1, line: 568, type: !28)
!1428 = !DILocation(line: 568, column: 11, scope: !295)
!1429 = !DILocation(line: 571, column: 7, scope: !1430)
!1430 = distinct !DILexicalBlock(scope: !295, file: !1, line: 571, column: 6)
!1431 = !DILocation(line: 571, column: 6, scope: !1430)
!1432 = !DILocation(line: 571, column: 17, scope: !1430)
!1433 = !DILocation(line: 571, column: 6, scope: !295)
!1434 = !DILocation(line: 572, column: 47, scope: !1435)
!1435 = distinct !DILexicalBlock(scope: !1430, file: !1, line: 571, column: 26)
!1436 = !DILocation(line: 572, column: 16, scope: !1435)
!1437 = !DILocation(line: 572, column: 4, scope: !1435)
!1438 = !DILocation(line: 572, column: 14, scope: !1435)
!1439 = !DILocation(line: 573, column: 8, scope: !1440)
!1440 = distinct !DILexicalBlock(scope: !1435, file: !1, line: 573, column: 7)
!1441 = !DILocation(line: 573, column: 7, scope: !1440)
!1442 = !DILocation(line: 573, column: 18, scope: !1440)
!1443 = !DILocation(line: 573, column: 7, scope: !1435)
!1444 = !DILocation(line: 574, column: 4, scope: !1440)
!1445 = !DILocation(line: 575, column: 2, scope: !1435)
!1446 = !DILocation(line: 577, column: 11, scope: !295)
!1447 = !DILocation(line: 577, column: 10, scope: !295)
!1448 = !DILocation(line: 577, column: 8, scope: !295)
!1449 = !DILocation(line: 583, column: 10, scope: !295)
!1450 = !DILocation(line: 583, column: 19, scope: !295)
!1451 = !DILocation(line: 583, column: 2, scope: !295)
!1452 = !DILocation(line: 585, column: 4, scope: !1453)
!1453 = distinct !DILexicalBlock(scope: !295, file: !1, line: 583, column: 25)
!1454 = !DILocation(line: 585, column: 11, scope: !1453)
!1455 = !DILocation(line: 585, column: 21, scope: !1453)
!1456 = !DILocation(line: 586, column: 4, scope: !1453)
!1457 = !DILocation(line: 589, column: 4, scope: !1458)
!1458 = distinct !DILexicalBlock(scope: !1453, file: !1, line: 588, column: 26)
!1459 = !DILocation(line: 589, column: 11, scope: !1458)
!1460 = !DILocation(line: 589, column: 21, scope: !1458)
!1461 = !DILocation(line: 593, column: 4, scope: !1458)
!1462 = !DILocation(line: 593, column: 27, scope: !1463)
!1463 = !DILexicalBlockFile(scope: !1458, file: !1, discriminator: 1)
!1464 = !DILocation(line: 593, column: 24, scope: !1463)
!1465 = !DILocation(line: 593, column: 39, scope: !1463)
!1466 = !DILocation(line: 593, column: 48, scope: !1463)
!1467 = !DILocation(line: 593, column: 37, scope: !1463)
!1468 = !DILocation(line: 593, column: 4, scope: !1463)
!1469 = !DILocation(line: 594, column: 5, scope: !1458)
!1470 = !DILocation(line: 593, column: 4, scope: !1471)
!1471 = !DILexicalBlockFile(scope: !1458, file: !1, discriminator: 2)
!1472 = !DILocation(line: 596, column: 29, scope: !1458)
!1473 = !DILocation(line: 596, column: 38, scope: !1458)
!1474 = !DILocation(line: 596, column: 4, scope: !1458)
!1475 = !DILocation(line: 596, column: 11, scope: !1458)
!1476 = !DILocation(line: 596, column: 27, scope: !1458)
!1477 = !DILocation(line: 600, column: 7, scope: !1458)
!1478 = !DILocation(line: 600, column: 16, scope: !1458)
!1479 = !DILocation(line: 600, column: 25, scope: !1458)
!1480 = !DILocation(line: 600, column: 29, scope: !1458)
!1481 = !DILocation(line: 599, column: 4, scope: !1458)
!1482 = !DILocation(line: 599, column: 11, scope: !1458)
!1483 = !DILocation(line: 599, column: 29, scope: !1458)
!1484 = !DILocation(line: 600, column: 5, scope: !1458)
!1485 = !DILocation(line: 602, column: 7, scope: !1458)
!1486 = !DILocation(line: 602, column: 16, scope: !1458)
!1487 = !DILocation(line: 602, column: 25, scope: !1458)
!1488 = !DILocation(line: 602, column: 29, scope: !1458)
!1489 = !DILocation(line: 601, column: 4, scope: !1458)
!1490 = !DILocation(line: 601, column: 11, scope: !1458)
!1491 = !DILocation(line: 601, column: 27, scope: !1458)
!1492 = !DILocation(line: 602, column: 5, scope: !1458)
!1493 = !DILocation(line: 603, column: 4, scope: !1458)
!1494 = !DILocation(line: 607, column: 4, scope: !1453)
!1495 = !DILocation(line: 614, column: 26, scope: !295)
!1496 = !DILocation(line: 614, column: 35, scope: !295)
!1497 = !DILocation(line: 614, column: 47, scope: !295)
!1498 = !DILocation(line: 615, column: 4, scope: !295)
!1499 = !DILocation(line: 615, column: 7, scope: !1500)
!1500 = !DILexicalBlockFile(scope: !295, file: !1, discriminator: 1)
!1501 = !DILocation(line: 615, column: 16, scope: !1500)
!1502 = !DILocation(line: 615, column: 33, scope: !1500)
!1503 = !DILocation(line: 614, column: 2, scope: !1500)
!1504 = !DILocation(line: 614, column: 9, scope: !1500)
!1505 = !DILocation(line: 614, column: 24, scope: !1500)
!1506 = !DILocation(line: 616, column: 2, scope: !295)
!1507 = !DILocation(line: 616, column: 9, scope: !295)
!1508 = !DILocation(line: 616, column: 20, scope: !295)
!1509 = !DILocation(line: 618, column: 17, scope: !295)
!1510 = !DILocation(line: 618, column: 29, scope: !295)
!1511 = !DILocation(line: 618, column: 2, scope: !295)
!1512 = !DILocation(line: 620, column: 33, scope: !295)
!1513 = !DILocation(line: 620, column: 40, scope: !295)
!1514 = !DILocation(line: 620, column: 9, scope: !295)
!1515 = !DILocation(line: 620, column: 2, scope: !295)
!1516 = !DILocation(line: 621, column: 1, scope: !295)
!1517 = !DILocalVariable(name: "lz_options", arg: 1, scope: !484, file: !1, line: 447, type: !312)
!1518 = !DILocation(line: 447, column: 33, scope: !484)
!1519 = !DILocalVariable(name: "options", arg: 2, scope: !484, file: !1, line: 447, type: !261)
!1520 = !DILocation(line: 447, column: 70, scope: !484)
!1521 = !DILocation(line: 451, column: 2, scope: !484)
!1522 = !DILocation(line: 451, column: 14, scope: !484)
!1523 = !DILocation(line: 451, column: 26, scope: !484)
!1524 = !DILocation(line: 452, column: 26, scope: !484)
!1525 = !DILocation(line: 452, column: 35, scope: !484)
!1526 = !DILocation(line: 452, column: 2, scope: !484)
!1527 = !DILocation(line: 452, column: 14, scope: !484)
!1528 = !DILocation(line: 452, column: 24, scope: !484)
!1529 = !DILocation(line: 453, column: 2, scope: !484)
!1530 = !DILocation(line: 453, column: 14, scope: !484)
!1531 = !DILocation(line: 453, column: 25, scope: !484)
!1532 = !DILocation(line: 454, column: 2, scope: !484)
!1533 = !DILocation(line: 454, column: 14, scope: !484)
!1534 = !DILocation(line: 454, column: 28, scope: !484)
!1535 = !DILocation(line: 455, column: 25, scope: !484)
!1536 = !DILocation(line: 455, column: 34, scope: !484)
!1537 = !DILocation(line: 455, column: 2, scope: !484)
!1538 = !DILocation(line: 455, column: 14, scope: !484)
!1539 = !DILocation(line: 455, column: 23, scope: !484)
!1540 = !DILocation(line: 456, column: 29, scope: !484)
!1541 = !DILocation(line: 456, column: 38, scope: !484)
!1542 = !DILocation(line: 456, column: 2, scope: !484)
!1543 = !DILocation(line: 456, column: 14, scope: !484)
!1544 = !DILocation(line: 456, column: 27, scope: !484)
!1545 = !DILocation(line: 457, column: 22, scope: !484)
!1546 = !DILocation(line: 457, column: 31, scope: !484)
!1547 = !DILocation(line: 457, column: 2, scope: !484)
!1548 = !DILocation(line: 457, column: 14, scope: !484)
!1549 = !DILocation(line: 457, column: 20, scope: !484)
!1550 = !DILocation(line: 458, column: 28, scope: !484)
!1551 = !DILocation(line: 458, column: 37, scope: !484)
!1552 = !DILocation(line: 458, column: 2, scope: !484)
!1553 = !DILocation(line: 458, column: 14, scope: !484)
!1554 = !DILocation(line: 458, column: 26, scope: !484)
!1555 = !DILocation(line: 459, column: 33, scope: !484)
!1556 = !DILocation(line: 459, column: 42, scope: !484)
!1557 = !DILocation(line: 459, column: 2, scope: !484)
!1558 = !DILocation(line: 459, column: 14, scope: !484)
!1559 = !DILocation(line: 459, column: 31, scope: !484)
!1560 = !DILocation(line: 460, column: 2, scope: !484)
!1561 = !DILocalVariable(name: "next", arg: 1, scope: !325, file: !1, line: 635, type: !328)
!1562 = !DILocation(line: 635, column: 41, scope: !325)
!1563 = !DILocalVariable(name: "allocator", arg: 2, scope: !325, file: !1, line: 635, type: !299)
!1564 = !DILocation(line: 635, column: 63, scope: !325)
!1565 = !DILocalVariable(name: "filters", arg: 3, scope: !325, file: !1, line: 636, type: !373)
!1566 = !DILocation(line: 636, column: 27, scope: !325)
!1567 = !DILocation(line: 639, column: 4, scope: !325)
!1568 = !DILocation(line: 639, column: 10, scope: !325)
!1569 = !DILocation(line: 639, column: 21, scope: !325)
!1570 = !DILocation(line: 638, column: 9, scope: !325)
!1571 = !DILocation(line: 638, column: 2, scope: !325)
!1572 = !DILocalVariable(name: "lz", arg: 1, scope: !487, file: !1, line: 625, type: !490)
!1573 = !DILocation(line: 625, column: 36, scope: !487)
!1574 = !DILocalVariable(name: "allocator", arg: 2, scope: !487, file: !1, line: 625, type: !299)
!1575 = !DILocation(line: 625, column: 56, scope: !487)
!1576 = !DILocalVariable(name: "options", arg: 3, scope: !487, file: !1, line: 626, type: !386)
!1577 = !DILocation(line: 626, column: 15, scope: !487)
!1578 = !DILocalVariable(name: "lz_options", arg: 4, scope: !487, file: !1, line: 626, type: !312)
!1579 = !DILocation(line: 626, column: 41, scope: !487)
!1580 = !DILocation(line: 628, column: 2, scope: !487)
!1581 = !DILocation(line: 628, column: 6, scope: !487)
!1582 = !DILocation(line: 628, column: 11, scope: !487)
!1583 = !DILocation(line: 630, column: 5, scope: !487)
!1584 = !DILocation(line: 630, column: 9, scope: !487)
!1585 = !DILocation(line: 630, column: 16, scope: !487)
!1586 = !DILocation(line: 630, column: 27, scope: !487)
!1587 = !DILocation(line: 630, column: 36, scope: !487)
!1588 = !DILocation(line: 629, column: 9, scope: !487)
!1589 = !DILocation(line: 629, column: 2, scope: !487)
!1590 = !DILocalVariable(name: "options", arg: 1, scope: !383, file: !1, line: 644, type: !386)
!1591 = !DILocation(line: 644, column: 40, scope: !383)
!1592 = !DILocalVariable(name: "lz_options", scope: !383, file: !1, line: 646, type: !313)
!1593 = !DILocation(line: 646, column: 18, scope: !383)
!1594 = !DILocalVariable(name: "lz_memusage", scope: !383, file: !1, line: 647, type: !23)
!1595 = !DILocation(line: 647, column: 11, scope: !383)
!1596 = !DILocation(line: 649, column: 24, scope: !1597)
!1597 = distinct !DILexicalBlock(scope: !383, file: !1, line: 649, column: 6)
!1598 = !DILocation(line: 649, column: 7, scope: !1597)
!1599 = !DILocation(line: 649, column: 6, scope: !383)
!1600 = !DILocation(line: 650, column: 3, scope: !1597)
!1601 = !DILocation(line: 652, column: 30, scope: !383)
!1602 = !DILocation(line: 652, column: 2, scope: !383)
!1603 = !DILocation(line: 654, column: 16, scope: !383)
!1604 = !DILocation(line: 654, column: 14, scope: !383)
!1605 = !DILocation(line: 655, column: 6, scope: !1606)
!1606 = distinct !DILexicalBlock(scope: !383, file: !1, line: 655, column: 6)
!1607 = !DILocation(line: 655, column: 18, scope: !1606)
!1608 = !DILocation(line: 655, column: 6, scope: !383)
!1609 = !DILocation(line: 656, column: 3, scope: !1606)
!1610 = !DILocation(line: 658, column: 42, scope: !383)
!1611 = !DILocation(line: 658, column: 40, scope: !383)
!1612 = !DILocation(line: 658, column: 2, scope: !383)
!1613 = !DILocation(line: 659, column: 1, scope: !383)
!1614 = !DILocalVariable(name: "options", arg: 1, scope: !388, file: !1, line: 663, type: !261)
!1615 = !DILocation(line: 663, column: 50, scope: !388)
!1616 = !DILocalVariable(name: "byte", arg: 2, scope: !388, file: !1, line: 663, type: !223)
!1617 = !DILocation(line: 663, column: 68, scope: !388)
!1618 = !DILocation(line: 665, column: 23, scope: !1619)
!1619 = distinct !DILexicalBlock(scope: !388, file: !1, line: 665, column: 6)
!1620 = !DILocation(line: 665, column: 7, scope: !1619)
!1621 = !DILocation(line: 665, column: 6, scope: !388)
!1622 = !DILocation(line: 666, column: 3, scope: !1619)
!1623 = !DILocation(line: 668, column: 11, scope: !388)
!1624 = !DILocation(line: 668, column: 20, scope: !388)
!1625 = !DILocation(line: 668, column: 23, scope: !388)
!1626 = !DILocation(line: 668, column: 29, scope: !388)
!1627 = !DILocation(line: 668, column: 38, scope: !388)
!1628 = !DILocation(line: 668, column: 27, scope: !388)
!1629 = !DILocation(line: 668, column: 42, scope: !388)
!1630 = !DILocation(line: 668, column: 48, scope: !388)
!1631 = !DILocation(line: 668, column: 57, scope: !388)
!1632 = !DILocation(line: 668, column: 46, scope: !388)
!1633 = !DILocation(line: 668, column: 10, scope: !388)
!1634 = !DILocation(line: 668, column: 3, scope: !388)
!1635 = !DILocation(line: 668, column: 8, scope: !388)
!1636 = !DILocation(line: 669, column: 2, scope: !388)
!1637 = !DILocation(line: 669, column: 2, scope: !1638)
!1638 = !DILexicalBlockFile(scope: !388, file: !1, discriminator: 1)
!1639 = !DILocation(line: 669, column: 2, scope: !1640)
!1640 = !DILexicalBlockFile(scope: !388, file: !1, discriminator: 2)
!1641 = !DILocation(line: 669, column: 2, scope: !1642)
!1642 = !DILexicalBlockFile(scope: !388, file: !1, discriminator: 3)
!1643 = !DILocation(line: 671, column: 2, scope: !388)
!1644 = !DILocation(line: 672, column: 1, scope: !388)
!1645 = !DILocalVariable(name: "options", arg: 1, scope: !505, file: !55, line: 33, type: !261)
!1646 = !DILocation(line: 33, column: 42, scope: !505)
!1647 = !DILocation(line: 35, column: 9, scope: !505)
!1648 = !DILocation(line: 35, column: 18, scope: !505)
!1649 = !DILocation(line: 35, column: 21, scope: !505)
!1650 = !DILocation(line: 35, column: 38, scope: !505)
!1651 = !DILocation(line: 35, column: 41, scope: !1652)
!1652 = !DILexicalBlockFile(scope: !505, file: !55, discriminator: 1)
!1653 = !DILocation(line: 35, column: 50, scope: !1652)
!1654 = !DILocation(line: 35, column: 53, scope: !1652)
!1655 = !DILocation(line: 36, column: 4, scope: !505)
!1656 = !DILocation(line: 36, column: 7, scope: !1652)
!1657 = !DILocation(line: 36, column: 16, scope: !1652)
!1658 = !DILocation(line: 36, column: 21, scope: !1652)
!1659 = !DILocation(line: 36, column: 30, scope: !1652)
!1660 = !DILocation(line: 36, column: 19, scope: !1652)
!1661 = !DILocation(line: 36, column: 33, scope: !1652)
!1662 = !DILocation(line: 37, column: 4, scope: !505)
!1663 = !DILocation(line: 37, column: 7, scope: !1652)
!1664 = !DILocation(line: 37, column: 16, scope: !1652)
!1665 = !DILocation(line: 37, column: 19, scope: !1652)
!1666 = !DILocation(line: 35, column: 2, scope: !1667)
!1667 = !DILexicalBlockFile(scope: !505, file: !55, discriminator: 2)
!1668 = !DILocalVariable(name: "options", arg: 1, scope: !391, file: !1, line: 677, type: !386)
!1669 = !DILocation(line: 677, column: 36, scope: !391)
!1670 = !DILocalVariable(name: "out", arg: 2, scope: !391, file: !1, line: 677, type: !223)
!1671 = !DILocation(line: 677, column: 54, scope: !391)
!1672 = !DILocalVariable(name: "opt", scope: !391, file: !1, line: 679, type: !1673)
!1673 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !261)
!1674 = !DILocation(line: 679, column: 33, scope: !391)
!1675 = !DILocation(line: 679, column: 39, scope: !391)
!1676 = !DILocation(line: 681, column: 30, scope: !1677)
!1677 = distinct !DILexicalBlock(scope: !391, file: !1, line: 681, column: 6)
!1678 = !DILocation(line: 681, column: 35, scope: !1677)
!1679 = !DILocation(line: 681, column: 6, scope: !1677)
!1680 = !DILocation(line: 681, column: 6, scope: !391)
!1681 = !DILocation(line: 682, column: 3, scope: !1677)
!1682 = !DILocation(line: 684, column: 2, scope: !391)
!1683 = !DILocation(line: 686, column: 2, scope: !391)
!1684 = !DILocation(line: 687, column: 1, scope: !391)
!1685 = !DILocalVariable(name: "buf", arg: 1, scope: !506, file: !507, line: 255, type: !223)
!1686 = !DILocation(line: 255, column: 20, scope: !506)
!1687 = !DILocalVariable(name: "num", arg: 2, scope: !506, file: !507, line: 255, type: !28)
!1688 = !DILocation(line: 255, column: 34, scope: !506)
!1689 = !DILocation(line: 257, column: 21, scope: !506)
!1690 = !DILocation(line: 257, column: 15, scope: !506)
!1691 = !DILocation(line: 257, column: 2, scope: !506)
!1692 = !DILocation(line: 257, column: 19, scope: !506)
!1693 = !DILocation(line: 258, column: 2, scope: !506)
!1694 = !DILocalVariable(name: "mode", arg: 1, scope: !394, file: !1, line: 692, type: !275)
!1695 = !DILocation(line: 692, column: 34, scope: !394)
!1696 = !DILocation(line: 694, column: 9, scope: !394)
!1697 = !DILocation(line: 694, column: 14, scope: !394)
!1698 = !DILocation(line: 694, column: 32, scope: !394)
!1699 = !DILocation(line: 694, column: 35, scope: !1700)
!1700 = !DILexicalBlockFile(scope: !394, file: !1, discriminator: 1)
!1701 = !DILocation(line: 694, column: 40, scope: !1700)
!1702 = !DILocation(line: 694, column: 32, scope: !1700)
!1703 = !DILocation(line: 694, column: 32, scope: !1704)
!1704 = !DILexicalBlockFile(scope: !394, file: !1, discriminator: 2)
!1705 = !DILocation(line: 694, column: 9, scope: !1704)
!1706 = !DILocation(line: 694, column: 2, scope: !1704)
!1707 = !DILocalVariable(name: "mf", arg: 1, scope: !401, file: !123, line: 268, type: !218)
!1708 = !DILocation(line: 268, column: 18, scope: !401)
!1709 = !DILocalVariable(name: "amount", arg: 2, scope: !401, file: !123, line: 268, type: !28)
!1710 = !DILocation(line: 268, column: 31, scope: !401)
!1711 = !DILocation(line: 270, column: 6, scope: !1712)
!1712 = distinct !DILexicalBlock(scope: !401, file: !123, line: 270, column: 6)
!1713 = !DILocation(line: 270, column: 13, scope: !1712)
!1714 = !DILocation(line: 270, column: 6, scope: !401)
!1715 = !DILocation(line: 271, column: 3, scope: !1716)
!1716 = distinct !DILexicalBlock(scope: !1712, file: !123, line: 270, column: 19)
!1717 = !DILocation(line: 271, column: 7, scope: !1716)
!1718 = !DILocation(line: 271, column: 12, scope: !1716)
!1719 = !DILocation(line: 271, column: 16, scope: !1716)
!1720 = !DILocation(line: 272, column: 21, scope: !1716)
!1721 = !DILocation(line: 272, column: 3, scope: !1716)
!1722 = !DILocation(line: 272, column: 7, scope: !1716)
!1723 = !DILocation(line: 272, column: 18, scope: !1716)
!1724 = !DILocation(line: 273, column: 2, scope: !1716)
!1725 = !DILocation(line: 274, column: 1, scope: !401)
!1726 = !DILocalVariable(name: "rc", arg: 1, scope: !402, file: !19, line: 67, type: !405)
!1727 = !DILocation(line: 67, column: 28, scope: !402)
!1728 = !DILocalVariable(name: "prob", arg: 2, scope: !402, file: !19, line: 67, type: !43)
!1729 = !DILocation(line: 67, column: 45, scope: !402)
!1730 = !DILocalVariable(name: "bit", arg: 3, scope: !402, file: !19, line: 67, type: !28)
!1731 = !DILocation(line: 67, column: 60, scope: !402)
!1732 = !DILocation(line: 69, column: 27, scope: !402)
!1733 = !DILocation(line: 69, column: 14, scope: !402)
!1734 = !DILocation(line: 69, column: 18, scope: !402)
!1735 = !DILocation(line: 69, column: 2, scope: !402)
!1736 = !DILocation(line: 69, column: 6, scope: !402)
!1737 = !DILocation(line: 69, column: 25, scope: !402)
!1738 = !DILocation(line: 70, column: 25, scope: !402)
!1739 = !DILocation(line: 70, column: 12, scope: !402)
!1740 = !DILocation(line: 70, column: 16, scope: !402)
!1741 = !DILocation(line: 70, column: 2, scope: !402)
!1742 = !DILocation(line: 70, column: 6, scope: !402)
!1743 = !DILocation(line: 70, column: 23, scope: !402)
!1744 = !DILocation(line: 71, column: 4, scope: !402)
!1745 = !DILocation(line: 71, column: 8, scope: !402)
!1746 = !DILocation(line: 71, column: 2, scope: !402)
!1747 = !DILocation(line: 72, column: 1, scope: !402)
!1748 = !DILocalVariable(name: "rc", arg: 1, scope: !406, file: !19, line: 76, type: !405)
!1749 = !DILocation(line: 76, column: 32, scope: !406)
!1750 = !DILocalVariable(name: "probs", arg: 2, scope: !406, file: !19, line: 76, type: !43)
!1751 = !DILocation(line: 76, column: 49, scope: !406)
!1752 = !DILocalVariable(name: "bit_count", arg: 3, scope: !406, file: !19, line: 77, type: !28)
!1753 = !DILocation(line: 77, column: 12, scope: !406)
!1754 = !DILocalVariable(name: "symbol", arg: 4, scope: !406, file: !19, line: 77, type: !28)
!1755 = !DILocation(line: 77, column: 32, scope: !406)
!1756 = !DILocalVariable(name: "model_index", scope: !406, file: !19, line: 79, type: !28)
!1757 = !DILocation(line: 79, column: 11, scope: !406)
!1758 = !DILocation(line: 81, column: 2, scope: !406)
!1759 = !DILocalVariable(name: "bit", scope: !1760, file: !19, line: 82, type: !433)
!1760 = distinct !DILexicalBlock(scope: !406, file: !19, line: 81, column: 5)
!1761 = !DILocation(line: 82, column: 18, scope: !1760)
!1762 = !DILocation(line: 82, column: 25, scope: !1760)
!1763 = !DILocation(line: 82, column: 35, scope: !1760)
!1764 = !DILocation(line: 82, column: 32, scope: !1760)
!1765 = !DILocation(line: 82, column: 48, scope: !1760)
!1766 = !DILocation(line: 83, column: 10, scope: !1760)
!1767 = !DILocation(line: 83, column: 21, scope: !1760)
!1768 = !DILocation(line: 83, column: 15, scope: !1760)
!1769 = !DILocation(line: 83, column: 35, scope: !1760)
!1770 = !DILocation(line: 83, column: 3, scope: !1760)
!1771 = !DILocation(line: 84, column: 18, scope: !1760)
!1772 = !DILocation(line: 84, column: 30, scope: !1760)
!1773 = !DILocation(line: 84, column: 38, scope: !1760)
!1774 = !DILocation(line: 84, column: 36, scope: !1760)
!1775 = !DILocation(line: 84, column: 15, scope: !1760)
!1776 = !DILocation(line: 85, column: 2, scope: !1760)
!1777 = !DILocation(line: 85, column: 11, scope: !1778)
!1778 = !DILexicalBlockFile(scope: !406, file: !19, discriminator: 1)
!1779 = !DILocation(line: 85, column: 21, scope: !1778)
!1780 = !DILocation(line: 85, column: 2, scope: !1778)
!1781 = !DILocation(line: 86, column: 1, scope: !406)
!1782 = !DILocalVariable(name: "rc", arg: 1, scope: !417, file: !19, line: 125, type: !405)
!1783 = !DILocation(line: 125, column: 34, scope: !417)
!1784 = !DILocalVariable(name: "out", arg: 2, scope: !417, file: !19, line: 126, type: !223)
!1785 = !DILocation(line: 126, column: 12, scope: !417)
!1786 = !DILocalVariable(name: "out_pos", arg: 3, scope: !417, file: !19, line: 126, type: !256)
!1787 = !DILocation(line: 126, column: 25, scope: !417)
!1788 = !DILocalVariable(name: "out_size", arg: 4, scope: !417, file: !19, line: 126, type: !34)
!1789 = !DILocation(line: 126, column: 41, scope: !417)
!1790 = !DILocation(line: 128, column: 17, scope: !1791)
!1791 = distinct !DILexicalBlock(scope: !417, file: !19, line: 128, column: 6)
!1792 = !DILocation(line: 128, column: 21, scope: !1791)
!1793 = !DILocation(line: 128, column: 6, scope: !1791)
!1794 = !DILocation(line: 128, column: 26, scope: !1791)
!1795 = !DILocation(line: 129, column: 4, scope: !1791)
!1796 = !DILocation(line: 129, column: 18, scope: !1797)
!1797 = !DILexicalBlockFile(scope: !1791, file: !19, discriminator: 1)
!1798 = !DILocation(line: 129, column: 22, scope: !1797)
!1799 = !DILocation(line: 129, column: 26, scope: !1797)
!1800 = !DILocation(line: 129, column: 7, scope: !1797)
!1801 = !DILocation(line: 129, column: 33, scope: !1797)
!1802 = !DILocation(line: 128, column: 6, scope: !1803)
!1803 = !DILexicalBlockFile(scope: !417, file: !19, discriminator: 1)
!1804 = !DILocation(line: 130, column: 3, scope: !1805)
!1805 = distinct !DILexicalBlock(scope: !1791, file: !19, line: 129, column: 39)
!1806 = !DILocation(line: 131, column: 9, scope: !1807)
!1807 = distinct !DILexicalBlock(scope: !1808, file: !19, line: 131, column: 8)
!1808 = distinct !DILexicalBlock(scope: !1805, file: !19, line: 130, column: 6)
!1809 = !DILocation(line: 131, column: 8, scope: !1807)
!1810 = !DILocation(line: 131, column: 20, scope: !1807)
!1811 = !DILocation(line: 131, column: 17, scope: !1807)
!1812 = !DILocation(line: 131, column: 8, scope: !1808)
!1813 = !DILocation(line: 132, column: 5, scope: !1807)
!1814 = !DILocation(line: 134, column: 20, scope: !1808)
!1815 = !DILocation(line: 134, column: 24, scope: !1808)
!1816 = !DILocation(line: 134, column: 42, scope: !1808)
!1817 = !DILocation(line: 134, column: 46, scope: !1808)
!1818 = !DILocation(line: 134, column: 50, scope: !1808)
!1819 = !DILocation(line: 134, column: 32, scope: !1808)
!1820 = !DILocation(line: 134, column: 30, scope: !1808)
!1821 = !DILocation(line: 134, column: 9, scope: !1808)
!1822 = !DILocation(line: 134, column: 8, scope: !1808)
!1823 = !DILocation(line: 134, column: 4, scope: !1808)
!1824 = !DILocation(line: 134, column: 18, scope: !1808)
!1825 = !DILocation(line: 135, column: 7, scope: !1808)
!1826 = !DILocation(line: 135, column: 4, scope: !1808)
!1827 = !DILocation(line: 136, column: 4, scope: !1808)
!1828 = !DILocation(line: 136, column: 8, scope: !1808)
!1829 = !DILocation(line: 136, column: 14, scope: !1808)
!1830 = !DILocation(line: 138, column: 3, scope: !1808)
!1831 = !DILocation(line: 138, column: 14, scope: !1832)
!1832 = !DILexicalBlockFile(scope: !1805, file: !19, discriminator: 1)
!1833 = !DILocation(line: 138, column: 18, scope: !1832)
!1834 = !DILocation(line: 138, column: 12, scope: !1832)
!1835 = !DILocation(line: 138, column: 29, scope: !1832)
!1836 = !DILocation(line: 138, column: 3, scope: !1832)
!1837 = !DILocation(line: 140, column: 16, scope: !1805)
!1838 = !DILocation(line: 140, column: 20, scope: !1805)
!1839 = !DILocation(line: 140, column: 24, scope: !1805)
!1840 = !DILocation(line: 140, column: 31, scope: !1805)
!1841 = !DILocation(line: 140, column: 15, scope: !1805)
!1842 = !DILocation(line: 140, column: 3, scope: !1805)
!1843 = !DILocation(line: 140, column: 7, scope: !1805)
!1844 = !DILocation(line: 140, column: 13, scope: !1805)
!1845 = !DILocation(line: 141, column: 2, scope: !1805)
!1846 = !DILocation(line: 143, column: 4, scope: !417)
!1847 = !DILocation(line: 143, column: 8, scope: !417)
!1848 = !DILocation(line: 143, column: 2, scope: !417)
!1849 = !DILocation(line: 144, column: 13, scope: !417)
!1850 = !DILocation(line: 144, column: 17, scope: !417)
!1851 = !DILocation(line: 144, column: 21, scope: !417)
!1852 = !DILocation(line: 144, column: 35, scope: !417)
!1853 = !DILocation(line: 144, column: 2, scope: !417)
!1854 = !DILocation(line: 144, column: 6, scope: !417)
!1855 = !DILocation(line: 144, column: 10, scope: !417)
!1856 = !DILocation(line: 146, column: 2, scope: !417)
!1857 = !DILocation(line: 147, column: 1, scope: !417)
!1858 = !DILocalVariable(name: "coder", arg: 1, scope: !426, file: !1, line: 49, type: !106)
!1859 = !DILocation(line: 49, column: 21, scope: !426)
!1860 = !DILocalVariable(name: "mf", arg: 2, scope: !426, file: !1, line: 49, type: !218)
!1861 = !DILocation(line: 49, column: 37, scope: !426)
!1862 = !DILocalVariable(name: "position", arg: 3, scope: !426, file: !1, line: 49, type: !28)
!1863 = !DILocation(line: 49, column: 50, scope: !426)
!1864 = !DILocalVariable(name: "cur_byte", scope: !426, file: !1, line: 52, type: !269)
!1865 = !DILocation(line: 52, column: 16, scope: !426)
!1866 = !DILocation(line: 53, column: 4, scope: !426)
!1867 = !DILocation(line: 53, column: 8, scope: !426)
!1868 = !DILocation(line: 53, column: 19, scope: !426)
!1869 = !DILocation(line: 53, column: 23, scope: !426)
!1870 = !DILocation(line: 53, column: 17, scope: !426)
!1871 = !DILocation(line: 52, column: 27, scope: !426)
!1872 = !DILocation(line: 52, column: 31, scope: !426)
!1873 = !DILocalVariable(name: "subcoder", scope: !426, file: !1, line: 54, type: !43)
!1874 = !DILocation(line: 54, column: 15, scope: !426)
!1875 = !DILocation(line: 54, column: 26, scope: !426)
!1876 = !DILocation(line: 58, column: 6, scope: !1877)
!1877 = distinct !DILexicalBlock(scope: !426, file: !1, line: 58, column: 6)
!1878 = !DILocation(line: 58, column: 6, scope: !426)
!1879 = !DILocation(line: 61, column: 15, scope: !1880)
!1880 = distinct !DILexicalBlock(scope: !1877, file: !1, line: 58, column: 38)
!1881 = !DILocation(line: 61, column: 22, scope: !1880)
!1882 = !DILocation(line: 61, column: 26, scope: !1880)
!1883 = !DILocation(line: 61, column: 39, scope: !1880)
!1884 = !DILocation(line: 61, column: 3, scope: !1880)
!1885 = !DILocation(line: 62, column: 2, scope: !1880)
!1886 = !DILocalVariable(name: "match_byte", scope: !1887, file: !1, line: 66, type: !269)
!1887 = distinct !DILexicalBlock(scope: !1877, file: !1, line: 62, column: 9)
!1888 = !DILocation(line: 66, column: 17, scope: !1887)
!1889 = !DILocation(line: 67, column: 5, scope: !1887)
!1890 = !DILocation(line: 67, column: 9, scope: !1887)
!1891 = !DILocation(line: 67, column: 20, scope: !1887)
!1892 = !DILocation(line: 67, column: 27, scope: !1887)
!1893 = !DILocation(line: 67, column: 18, scope: !1887)
!1894 = !DILocation(line: 67, column: 35, scope: !1887)
!1895 = !DILocation(line: 68, column: 7, scope: !1887)
!1896 = !DILocation(line: 68, column: 11, scope: !1887)
!1897 = !DILocation(line: 68, column: 5, scope: !1887)
!1898 = !DILocation(line: 66, column: 30, scope: !1887)
!1899 = !DILocation(line: 66, column: 34, scope: !1887)
!1900 = !DILocation(line: 69, column: 20, scope: !1887)
!1901 = !DILocation(line: 69, column: 27, scope: !1887)
!1902 = !DILocation(line: 69, column: 31, scope: !1887)
!1903 = !DILocation(line: 69, column: 41, scope: !1887)
!1904 = !DILocation(line: 69, column: 53, scope: !1887)
!1905 = !DILocation(line: 69, column: 3, scope: !1887)
!1906 = !DILocation(line: 72, column: 2, scope: !426)
!1907 = !DILocation(line: 72, column: 2, scope: !1908)
!1908 = !DILexicalBlockFile(scope: !426, file: !1, discriminator: 1)
!1909 = !DILocation(line: 72, column: 2, scope: !1910)
!1910 = !DILexicalBlockFile(scope: !426, file: !1, discriminator: 2)
!1911 = !DILocation(line: 72, column: 2, scope: !1912)
!1912 = !DILexicalBlockFile(scope: !426, file: !1, discriminator: 3)
!1913 = !DILocation(line: 72, column: 2, scope: !1914)
!1914 = !DILexicalBlockFile(scope: !426, file: !1, discriminator: 4)
!1915 = !DILocation(line: 72, column: 2, scope: !1916)
!1916 = !DILexicalBlockFile(scope: !426, file: !1, discriminator: 5)
!1917 = !DILocation(line: 72, column: 2, scope: !1918)
!1918 = !DILexicalBlockFile(scope: !426, file: !1, discriminator: 6)
!1919 = !DILocation(line: 73, column: 1, scope: !426)
!1920 = !DILocalVariable(name: "coder", arg: 1, scope: !430, file: !1, line: 199, type: !106)
!1921 = !DILocation(line: 199, column: 23, scope: !430)
!1922 = !DILocalVariable(name: "pos_state", arg: 2, scope: !430, file: !1, line: 199, type: !433)
!1923 = !DILocation(line: 199, column: 45, scope: !430)
!1924 = !DILocalVariable(name: "rep", arg: 3, scope: !430, file: !1, line: 200, type: !433)
!1925 = !DILocation(line: 200, column: 18, scope: !430)
!1926 = !DILocalVariable(name: "len", arg: 4, scope: !430, file: !1, line: 200, type: !433)
!1927 = !DILocation(line: 200, column: 38, scope: !430)
!1928 = !DILocation(line: 202, column: 6, scope: !1929)
!1929 = distinct !DILexicalBlock(scope: !430, file: !1, line: 202, column: 6)
!1930 = !DILocation(line: 202, column: 10, scope: !1929)
!1931 = !DILocation(line: 202, column: 6, scope: !430)
!1932 = !DILocation(line: 203, column: 11, scope: !1933)
!1933 = distinct !DILexicalBlock(scope: !1929, file: !1, line: 202, column: 16)
!1934 = !DILocation(line: 203, column: 18, scope: !1933)
!1935 = !DILocation(line: 203, column: 38, scope: !1933)
!1936 = !DILocation(line: 203, column: 45, scope: !1933)
!1937 = !DILocation(line: 203, column: 23, scope: !1933)
!1938 = !DILocation(line: 203, column: 30, scope: !1933)
!1939 = !DILocation(line: 203, column: 3, scope: !1933)
!1940 = !DILocation(line: 204, column: 11, scope: !1933)
!1941 = !DILocation(line: 204, column: 18, scope: !1933)
!1942 = !DILocation(line: 205, column: 40, scope: !1933)
!1943 = !DILocation(line: 205, column: 6, scope: !1933)
!1944 = !DILocation(line: 205, column: 26, scope: !1933)
!1945 = !DILocation(line: 205, column: 33, scope: !1933)
!1946 = !DILocation(line: 205, column: 13, scope: !1933)
!1947 = !DILocation(line: 206, column: 5, scope: !1933)
!1948 = !DILocation(line: 206, column: 9, scope: !1933)
!1949 = !DILocation(line: 204, column: 3, scope: !1933)
!1950 = !DILocation(line: 207, column: 2, scope: !1933)
!1951 = !DILocalVariable(name: "distance", scope: !1952, file: !1, line: 208, type: !433)
!1952 = distinct !DILexicalBlock(scope: !1929, file: !1, line: 207, column: 9)
!1953 = !DILocation(line: 208, column: 18, scope: !1952)
!1954 = !DILocation(line: 208, column: 41, scope: !1952)
!1955 = !DILocation(line: 208, column: 29, scope: !1952)
!1956 = !DILocation(line: 208, column: 36, scope: !1952)
!1957 = !DILocation(line: 209, column: 11, scope: !1952)
!1958 = !DILocation(line: 209, column: 18, scope: !1952)
!1959 = !DILocation(line: 209, column: 38, scope: !1952)
!1960 = !DILocation(line: 209, column: 45, scope: !1952)
!1961 = !DILocation(line: 209, column: 23, scope: !1952)
!1962 = !DILocation(line: 209, column: 30, scope: !1952)
!1963 = !DILocation(line: 209, column: 3, scope: !1952)
!1964 = !DILocation(line: 211, column: 7, scope: !1965)
!1965 = distinct !DILexicalBlock(scope: !1952, file: !1, line: 211, column: 7)
!1966 = !DILocation(line: 211, column: 11, scope: !1965)
!1967 = !DILocation(line: 211, column: 7, scope: !1952)
!1968 = !DILocation(line: 212, column: 12, scope: !1969)
!1969 = distinct !DILexicalBlock(scope: !1965, file: !1, line: 211, column: 17)
!1970 = !DILocation(line: 212, column: 19, scope: !1969)
!1971 = !DILocation(line: 212, column: 39, scope: !1969)
!1972 = !DILocation(line: 212, column: 46, scope: !1969)
!1973 = !DILocation(line: 212, column: 24, scope: !1969)
!1974 = !DILocation(line: 212, column: 31, scope: !1969)
!1975 = !DILocation(line: 212, column: 4, scope: !1969)
!1976 = !DILocation(line: 213, column: 3, scope: !1969)
!1977 = !DILocation(line: 214, column: 12, scope: !1978)
!1978 = distinct !DILexicalBlock(scope: !1965, file: !1, line: 213, column: 10)
!1979 = !DILocation(line: 214, column: 19, scope: !1978)
!1980 = !DILocation(line: 214, column: 39, scope: !1978)
!1981 = !DILocation(line: 214, column: 46, scope: !1978)
!1982 = !DILocation(line: 214, column: 24, scope: !1978)
!1983 = !DILocation(line: 214, column: 31, scope: !1978)
!1984 = !DILocation(line: 214, column: 4, scope: !1978)
!1985 = !DILocation(line: 215, column: 12, scope: !1978)
!1986 = !DILocation(line: 215, column: 19, scope: !1978)
!1987 = !DILocation(line: 215, column: 39, scope: !1978)
!1988 = !DILocation(line: 215, column: 46, scope: !1978)
!1989 = !DILocation(line: 215, column: 24, scope: !1978)
!1990 = !DILocation(line: 215, column: 31, scope: !1978)
!1991 = !DILocation(line: 216, column: 6, scope: !1978)
!1992 = !DILocation(line: 216, column: 10, scope: !1978)
!1993 = !DILocation(line: 215, column: 4, scope: !1978)
!1994 = !DILocation(line: 218, column: 8, scope: !1995)
!1995 = distinct !DILexicalBlock(scope: !1978, file: !1, line: 218, column: 8)
!1996 = !DILocation(line: 218, column: 12, scope: !1995)
!1997 = !DILocation(line: 218, column: 8, scope: !1978)
!1998 = !DILocation(line: 219, column: 22, scope: !1995)
!1999 = !DILocation(line: 219, column: 29, scope: !1995)
!2000 = !DILocation(line: 219, column: 5, scope: !1995)
!2001 = !DILocation(line: 219, column: 12, scope: !1995)
!2002 = !DILocation(line: 219, column: 20, scope: !1995)
!2003 = !DILocation(line: 221, column: 21, scope: !1978)
!2004 = !DILocation(line: 221, column: 28, scope: !1978)
!2005 = !DILocation(line: 221, column: 4, scope: !1978)
!2006 = !DILocation(line: 221, column: 11, scope: !1978)
!2007 = !DILocation(line: 221, column: 19, scope: !1978)
!2008 = !DILocation(line: 224, column: 20, scope: !1952)
!2009 = !DILocation(line: 224, column: 27, scope: !1952)
!2010 = !DILocation(line: 224, column: 3, scope: !1952)
!2011 = !DILocation(line: 224, column: 10, scope: !1952)
!2012 = !DILocation(line: 224, column: 18, scope: !1952)
!2013 = !DILocation(line: 225, column: 20, scope: !1952)
!2014 = !DILocation(line: 225, column: 3, scope: !1952)
!2015 = !DILocation(line: 225, column: 10, scope: !1952)
!2016 = !DILocation(line: 225, column: 18, scope: !1952)
!2017 = !DILocation(line: 228, column: 6, scope: !2018)
!2018 = distinct !DILexicalBlock(scope: !430, file: !1, line: 228, column: 6)
!2019 = !DILocation(line: 228, column: 10, scope: !2018)
!2020 = !DILocation(line: 228, column: 6, scope: !430)
!2021 = !DILocation(line: 229, column: 3, scope: !2022)
!2022 = distinct !DILexicalBlock(scope: !2018, file: !1, line: 228, column: 16)
!2023 = !DILocation(line: 230, column: 2, scope: !2022)
!2024 = !DILocation(line: 231, column: 11, scope: !2025)
!2025 = distinct !DILexicalBlock(scope: !2018, file: !1, line: 230, column: 9)
!2026 = !DILocation(line: 231, column: 18, scope: !2025)
!2027 = !DILocation(line: 231, column: 23, scope: !2025)
!2028 = !DILocation(line: 231, column: 30, scope: !2025)
!2029 = !DILocation(line: 231, column: 47, scope: !2025)
!2030 = !DILocation(line: 231, column: 58, scope: !2025)
!2031 = !DILocation(line: 232, column: 5, scope: !2025)
!2032 = !DILocation(line: 232, column: 12, scope: !2025)
!2033 = !DILocation(line: 231, column: 3, scope: !2025)
!2034 = !DILocation(line: 233, column: 3, scope: !2025)
!2035 = !DILocation(line: 235, column: 1, scope: !430)
!2036 = !DILocalVariable(name: "coder", arg: 1, scope: !456, file: !1, line: 149, type: !106)
!2037 = !DILocation(line: 149, column: 19, scope: !456)
!2038 = !DILocalVariable(name: "pos_state", arg: 2, scope: !456, file: !1, line: 149, type: !433)
!2039 = !DILocation(line: 149, column: 41, scope: !456)
!2040 = !DILocalVariable(name: "distance", arg: 3, scope: !456, file: !1, line: 150, type: !433)
!2041 = !DILocation(line: 150, column: 18, scope: !456)
!2042 = !DILocalVariable(name: "len", arg: 4, scope: !456, file: !1, line: 150, type: !433)
!2043 = !DILocation(line: 150, column: 43, scope: !456)
!2044 = !DILocalVariable(name: "pos_slot", scope: !456, file: !1, line: 152, type: !28)
!2045 = !DILocation(line: 152, column: 11, scope: !456)
!2046 = !DILocalVariable(name: "len_to_pos_state", scope: !456, file: !1, line: 153, type: !28)
!2047 = !DILocation(line: 153, column: 11, scope: !456)
!2048 = !DILocation(line: 155, column: 2, scope: !456)
!2049 = !DILocation(line: 157, column: 10, scope: !456)
!2050 = !DILocation(line: 157, column: 17, scope: !456)
!2051 = !DILocation(line: 157, column: 22, scope: !456)
!2052 = !DILocation(line: 157, column: 29, scope: !456)
!2053 = !DILocation(line: 157, column: 48, scope: !456)
!2054 = !DILocation(line: 157, column: 59, scope: !456)
!2055 = !DILocation(line: 158, column: 4, scope: !456)
!2056 = !DILocation(line: 158, column: 11, scope: !456)
!2057 = !DILocation(line: 157, column: 2, scope: !456)
!2058 = !DILocation(line: 160, column: 26, scope: !456)
!2059 = !DILocation(line: 160, column: 13, scope: !456)
!2060 = !DILocation(line: 160, column: 11, scope: !456)
!2061 = !DILocation(line: 161, column: 21, scope: !456)
!2062 = !DILocation(line: 161, column: 21, scope: !2063)
!2063 = !DILexicalBlockFile(scope: !456, file: !1, discriminator: 1)
!2064 = !DILocation(line: 161, column: 21, scope: !2065)
!2065 = !DILexicalBlockFile(scope: !456, file: !1, discriminator: 2)
!2066 = !DILocation(line: 161, column: 21, scope: !2067)
!2067 = !DILexicalBlockFile(scope: !456, file: !1, discriminator: 3)
!2068 = !DILocation(line: 161, column: 19, scope: !2067)
!2069 = !DILocation(line: 162, column: 14, scope: !456)
!2070 = !DILocation(line: 162, column: 21, scope: !456)
!2071 = !DILocation(line: 162, column: 41, scope: !456)
!2072 = !DILocation(line: 162, column: 25, scope: !456)
!2073 = !DILocation(line: 162, column: 32, scope: !456)
!2074 = !DILocation(line: 163, column: 19, scope: !456)
!2075 = !DILocation(line: 162, column: 2, scope: !456)
!2076 = !DILocation(line: 165, column: 6, scope: !2077)
!2077 = distinct !DILexicalBlock(scope: !456, file: !1, line: 165, column: 6)
!2078 = !DILocation(line: 165, column: 15, scope: !2077)
!2079 = !DILocation(line: 165, column: 6, scope: !456)
!2080 = !DILocalVariable(name: "footer_bits", scope: !2081, file: !1, line: 166, type: !433)
!2081 = distinct !DILexicalBlock(scope: !2077, file: !1, line: 165, column: 41)
!2082 = !DILocation(line: 166, column: 18, scope: !2081)
!2083 = !DILocation(line: 166, column: 33, scope: !2081)
!2084 = !DILocation(line: 166, column: 42, scope: !2081)
!2085 = !DILocation(line: 166, column: 48, scope: !2081)
!2086 = !DILocalVariable(name: "base", scope: !2081, file: !1, line: 167, type: !433)
!2087 = !DILocation(line: 167, column: 18, scope: !2081)
!2088 = !DILocation(line: 167, column: 31, scope: !2081)
!2089 = !DILocation(line: 167, column: 40, scope: !2081)
!2090 = !DILocation(line: 167, column: 28, scope: !2081)
!2091 = !DILocation(line: 167, column: 49, scope: !2081)
!2092 = !DILocation(line: 167, column: 46, scope: !2081)
!2093 = !DILocalVariable(name: "pos_reduced", scope: !2081, file: !1, line: 168, type: !433)
!2094 = !DILocation(line: 168, column: 18, scope: !2081)
!2095 = !DILocation(line: 168, column: 32, scope: !2081)
!2096 = !DILocation(line: 168, column: 43, scope: !2081)
!2097 = !DILocation(line: 168, column: 41, scope: !2081)
!2098 = !DILocation(line: 170, column: 7, scope: !2099)
!2099 = distinct !DILexicalBlock(scope: !2081, file: !1, line: 170, column: 7)
!2100 = !DILocation(line: 170, column: 16, scope: !2099)
!2101 = !DILocation(line: 170, column: 7, scope: !2081)
!2102 = !DILocation(line: 173, column: 24, scope: !2103)
!2103 = distinct !DILexicalBlock(scope: !2099, file: !1, line: 170, column: 39)
!2104 = !DILocation(line: 173, column: 31, scope: !2103)
!2105 = !DILocation(line: 174, column: 5, scope: !2103)
!2106 = !DILocation(line: 174, column: 12, scope: !2103)
!2107 = !DILocation(line: 174, column: 26, scope: !2103)
!2108 = !DILocation(line: 174, column: 24, scope: !2103)
!2109 = !DILocation(line: 174, column: 33, scope: !2103)
!2110 = !DILocation(line: 174, column: 31, scope: !2103)
!2111 = !DILocation(line: 174, column: 42, scope: !2103)
!2112 = !DILocation(line: 175, column: 5, scope: !2103)
!2113 = !DILocation(line: 175, column: 18, scope: !2103)
!2114 = !DILocation(line: 173, column: 4, scope: !2103)
!2115 = !DILocation(line: 176, column: 3, scope: !2103)
!2116 = !DILocation(line: 177, column: 15, scope: !2117)
!2117 = distinct !DILexicalBlock(scope: !2099, file: !1, line: 176, column: 10)
!2118 = !DILocation(line: 177, column: 22, scope: !2117)
!2119 = !DILocation(line: 177, column: 26, scope: !2117)
!2120 = !DILocation(line: 177, column: 38, scope: !2117)
!2121 = !DILocation(line: 178, column: 6, scope: !2117)
!2122 = !DILocation(line: 178, column: 18, scope: !2117)
!2123 = !DILocation(line: 177, column: 4, scope: !2117)
!2124 = !DILocation(line: 180, column: 7, scope: !2117)
!2125 = !DILocation(line: 180, column: 14, scope: !2117)
!2126 = !DILocation(line: 180, column: 18, scope: !2117)
!2127 = !DILocation(line: 180, column: 25, scope: !2117)
!2128 = !DILocation(line: 181, column: 18, scope: !2117)
!2129 = !DILocation(line: 181, column: 30, scope: !2117)
!2130 = !DILocation(line: 179, column: 4, scope: !2117)
!2131 = !DILocation(line: 182, column: 6, scope: !2117)
!2132 = !DILocation(line: 182, column: 13, scope: !2117)
!2133 = !DILocation(line: 182, column: 4, scope: !2117)
!2134 = !DILocation(line: 184, column: 2, scope: !2081)
!2135 = !DILocation(line: 186, column: 19, scope: !456)
!2136 = !DILocation(line: 186, column: 26, scope: !456)
!2137 = !DILocation(line: 186, column: 2, scope: !456)
!2138 = !DILocation(line: 186, column: 9, scope: !456)
!2139 = !DILocation(line: 186, column: 17, scope: !456)
!2140 = !DILocation(line: 187, column: 19, scope: !456)
!2141 = !DILocation(line: 187, column: 26, scope: !456)
!2142 = !DILocation(line: 187, column: 2, scope: !456)
!2143 = !DILocation(line: 187, column: 9, scope: !456)
!2144 = !DILocation(line: 187, column: 17, scope: !456)
!2145 = !DILocation(line: 188, column: 19, scope: !456)
!2146 = !DILocation(line: 188, column: 26, scope: !456)
!2147 = !DILocation(line: 188, column: 2, scope: !456)
!2148 = !DILocation(line: 188, column: 9, scope: !456)
!2149 = !DILocation(line: 188, column: 17, scope: !456)
!2150 = !DILocation(line: 189, column: 19, scope: !456)
!2151 = !DILocation(line: 189, column: 2, scope: !456)
!2152 = !DILocation(line: 189, column: 9, scope: !456)
!2153 = !DILocation(line: 189, column: 17, scope: !456)
!2154 = !DILocation(line: 190, column: 4, scope: !456)
!2155 = !DILocation(line: 190, column: 11, scope: !456)
!2156 = !DILocation(line: 190, column: 2, scope: !456)
!2157 = !DILocation(line: 191, column: 1, scope: !456)
!2158 = !DILocalVariable(name: "rc", arg: 1, scope: !429, file: !1, line: 24, type: !405)
!2159 = !DILocation(line: 24, column: 37, scope: !429)
!2160 = !DILocalVariable(name: "subcoder", arg: 2, scope: !429, file: !1, line: 24, type: !43)
!2161 = !DILocation(line: 24, column: 54, scope: !429)
!2162 = !DILocalVariable(name: "match_byte", arg: 3, scope: !429, file: !1, line: 25, type: !28)
!2163 = !DILocation(line: 25, column: 12, scope: !429)
!2164 = !DILocalVariable(name: "symbol", arg: 4, scope: !429, file: !1, line: 25, type: !28)
!2165 = !DILocation(line: 25, column: 33, scope: !429)
!2166 = !DILocalVariable(name: "offset", scope: !429, file: !1, line: 27, type: !28)
!2167 = !DILocation(line: 27, column: 11, scope: !429)
!2168 = !DILocation(line: 28, column: 9, scope: !429)
!2169 = !DILocation(line: 30, column: 2, scope: !429)
!2170 = !DILocalVariable(name: "match_bit", scope: !2171, file: !1, line: 31, type: !28)
!2171 = distinct !DILexicalBlock(scope: !429, file: !1, line: 30, column: 5)
!2172 = !DILocation(line: 31, column: 12, scope: !2171)
!2173 = !DILocalVariable(name: "subcoder_index", scope: !2171, file: !1, line: 32, type: !28)
!2174 = !DILocation(line: 32, column: 12, scope: !2171)
!2175 = !DILocalVariable(name: "bit", scope: !2171, file: !1, line: 33, type: !28)
!2176 = !DILocation(line: 33, column: 12, scope: !2171)
!2177 = !DILocation(line: 35, column: 14, scope: !2171)
!2178 = !DILocation(line: 36, column: 15, scope: !2171)
!2179 = !DILocation(line: 36, column: 28, scope: !2171)
!2180 = !DILocation(line: 36, column: 26, scope: !2171)
!2181 = !DILocation(line: 36, column: 13, scope: !2171)
!2182 = !DILocation(line: 37, column: 20, scope: !2171)
!2183 = !DILocation(line: 37, column: 29, scope: !2171)
!2184 = !DILocation(line: 37, column: 27, scope: !2171)
!2185 = !DILocation(line: 37, column: 42, scope: !2171)
!2186 = !DILocation(line: 37, column: 49, scope: !2171)
!2187 = !DILocation(line: 37, column: 39, scope: !2171)
!2188 = !DILocation(line: 37, column: 18, scope: !2171)
!2189 = !DILocation(line: 38, column: 10, scope: !2171)
!2190 = !DILocation(line: 38, column: 17, scope: !2171)
!2191 = !DILocation(line: 38, column: 23, scope: !2171)
!2192 = !DILocation(line: 38, column: 7, scope: !2171)
!2193 = !DILocation(line: 39, column: 10, scope: !2171)
!2194 = !DILocation(line: 39, column: 24, scope: !2171)
!2195 = !DILocation(line: 39, column: 15, scope: !2171)
!2196 = !DILocation(line: 39, column: 41, scope: !2171)
!2197 = !DILocation(line: 39, column: 3, scope: !2171)
!2198 = !DILocation(line: 41, column: 10, scope: !2171)
!2199 = !DILocation(line: 42, column: 15, scope: !2171)
!2200 = !DILocation(line: 42, column: 28, scope: !2171)
!2201 = !DILocation(line: 42, column: 26, scope: !2171)
!2202 = !DILocation(line: 42, column: 13, scope: !2171)
!2203 = !DILocation(line: 42, column: 10, scope: !2171)
!2204 = !DILocation(line: 44, column: 2, scope: !2171)
!2205 = !DILocation(line: 44, column: 11, scope: !2206)
!2206 = !DILexicalBlockFile(scope: !429, file: !1, discriminator: 1)
!2207 = !DILocation(line: 44, column: 18, scope: !2206)
!2208 = !DILocation(line: 44, column: 2, scope: !2206)
!2209 = !DILocation(line: 45, column: 1, scope: !429)
!2210 = !DILocalVariable(name: "rc", arg: 1, scope: !434, file: !1, line: 113, type: !405)
!2211 = !DILocation(line: 113, column: 28, scope: !434)
!2212 = !DILocalVariable(name: "lc", arg: 2, scope: !434, file: !1, line: 113, type: !437)
!2213 = !DILocation(line: 113, column: 53, scope: !434)
!2214 = !DILocalVariable(name: "pos_state", arg: 3, scope: !434, file: !1, line: 114, type: !433)
!2215 = !DILocation(line: 114, column: 18, scope: !434)
!2216 = !DILocalVariable(name: "len", arg: 4, scope: !434, file: !1, line: 114, type: !28)
!2217 = !DILocation(line: 114, column: 38, scope: !434)
!2218 = !DILocalVariable(name: "fast_mode", arg: 5, scope: !434, file: !1, line: 114, type: !438)
!2219 = !DILocation(line: 114, column: 54, scope: !434)
!2220 = !DILocation(line: 116, column: 2, scope: !434)
!2221 = !DILocation(line: 116, column: 2, scope: !2222)
!2222 = !DILexicalBlockFile(scope: !434, file: !1, discriminator: 1)
!2223 = !DILocation(line: 116, column: 2, scope: !2224)
!2224 = !DILexicalBlockFile(scope: !434, file: !1, discriminator: 2)
!2225 = !DILocation(line: 116, column: 2, scope: !2226)
!2226 = !DILexicalBlockFile(scope: !434, file: !1, discriminator: 3)
!2227 = !DILocation(line: 117, column: 6, scope: !434)
!2228 = !DILocation(line: 119, column: 6, scope: !2229)
!2229 = distinct !DILexicalBlock(scope: !434, file: !1, line: 119, column: 6)
!2230 = !DILocation(line: 119, column: 10, scope: !2229)
!2231 = !DILocation(line: 119, column: 6, scope: !434)
!2232 = !DILocation(line: 120, column: 10, scope: !2233)
!2233 = distinct !DILexicalBlock(scope: !2229, file: !1, line: 119, column: 29)
!2234 = !DILocation(line: 120, column: 15, scope: !2233)
!2235 = !DILocation(line: 120, column: 19, scope: !2233)
!2236 = !DILocation(line: 120, column: 3, scope: !2233)
!2237 = !DILocation(line: 121, column: 14, scope: !2233)
!2238 = !DILocation(line: 121, column: 26, scope: !2233)
!2239 = !DILocation(line: 121, column: 18, scope: !2233)
!2240 = !DILocation(line: 121, column: 22, scope: !2233)
!2241 = !DILocation(line: 121, column: 52, scope: !2233)
!2242 = !DILocation(line: 121, column: 3, scope: !2233)
!2243 = !DILocation(line: 122, column: 2, scope: !2233)
!2244 = !DILocation(line: 123, column: 10, scope: !2245)
!2245 = distinct !DILexicalBlock(scope: !2229, file: !1, line: 122, column: 9)
!2246 = !DILocation(line: 123, column: 15, scope: !2245)
!2247 = !DILocation(line: 123, column: 19, scope: !2245)
!2248 = !DILocation(line: 123, column: 3, scope: !2245)
!2249 = !DILocation(line: 124, column: 7, scope: !2245)
!2250 = !DILocation(line: 126, column: 7, scope: !2251)
!2251 = distinct !DILexicalBlock(scope: !2245, file: !1, line: 126, column: 7)
!2252 = !DILocation(line: 126, column: 11, scope: !2251)
!2253 = !DILocation(line: 126, column: 7, scope: !2245)
!2254 = !DILocation(line: 127, column: 11, scope: !2255)
!2255 = distinct !DILexicalBlock(scope: !2251, file: !1, line: 126, column: 30)
!2256 = !DILocation(line: 127, column: 16, scope: !2255)
!2257 = !DILocation(line: 127, column: 20, scope: !2255)
!2258 = !DILocation(line: 127, column: 4, scope: !2255)
!2259 = !DILocation(line: 128, column: 15, scope: !2255)
!2260 = !DILocation(line: 128, column: 27, scope: !2255)
!2261 = !DILocation(line: 128, column: 19, scope: !2255)
!2262 = !DILocation(line: 128, column: 23, scope: !2255)
!2263 = !DILocation(line: 128, column: 53, scope: !2255)
!2264 = !DILocation(line: 128, column: 4, scope: !2255)
!2265 = !DILocation(line: 129, column: 3, scope: !2255)
!2266 = !DILocation(line: 130, column: 11, scope: !2267)
!2267 = distinct !DILexicalBlock(scope: !2251, file: !1, line: 129, column: 10)
!2268 = !DILocation(line: 130, column: 16, scope: !2267)
!2269 = !DILocation(line: 130, column: 20, scope: !2267)
!2270 = !DILocation(line: 130, column: 4, scope: !2267)
!2271 = !DILocation(line: 131, column: 8, scope: !2267)
!2272 = !DILocation(line: 132, column: 15, scope: !2267)
!2273 = !DILocation(line: 132, column: 19, scope: !2267)
!2274 = !DILocation(line: 132, column: 23, scope: !2267)
!2275 = !DILocation(line: 132, column: 44, scope: !2267)
!2276 = !DILocation(line: 132, column: 4, scope: !2267)
!2277 = !DILocation(line: 138, column: 7, scope: !2278)
!2278 = distinct !DILexicalBlock(scope: !434, file: !1, line: 138, column: 6)
!2279 = !DILocation(line: 138, column: 6, scope: !434)
!2280 = !DILocation(line: 139, column: 22, scope: !2281)
!2281 = distinct !DILexicalBlock(scope: !2278, file: !1, line: 139, column: 7)
!2282 = !DILocation(line: 139, column: 9, scope: !2281)
!2283 = !DILocation(line: 139, column: 13, scope: !2281)
!2284 = !DILocation(line: 139, column: 7, scope: !2281)
!2285 = !DILocation(line: 139, column: 33, scope: !2281)
!2286 = !DILocation(line: 139, column: 7, scope: !2278)
!2287 = !DILocation(line: 140, column: 25, scope: !2281)
!2288 = !DILocation(line: 140, column: 29, scope: !2281)
!2289 = !DILocation(line: 140, column: 4, scope: !2281)
!2290 = !DILocation(line: 139, column: 36, scope: !2291)
!2291 = !DILexicalBlockFile(scope: !2281, file: !1, discriminator: 1)
!2292 = !DILocation(line: 141, column: 1, scope: !434)
!2293 = !DILocalVariable(name: "lc", arg: 1, scope: !439, file: !1, line: 81, type: !437)
!2294 = !DILocation(line: 81, column: 43, scope: !439)
!2295 = !DILocalVariable(name: "pos_state", arg: 2, scope: !439, file: !1, line: 81, type: !433)
!2296 = !DILocation(line: 81, column: 62, scope: !439)
!2297 = !DILocalVariable(name: "a0", scope: !439, file: !1, line: 83, type: !28)
!2298 = !DILocation(line: 83, column: 11, scope: !439)
!2299 = !DILocalVariable(name: "a1", scope: !439, file: !1, line: 83, type: !28)
!2300 = !DILocation(line: 83, column: 15, scope: !439)
!2301 = !DILocalVariable(name: "b0", scope: !439, file: !1, line: 83, type: !28)
!2302 = !DILocation(line: 83, column: 19, scope: !439)
!2303 = !DILocalVariable(name: "b1", scope: !439, file: !1, line: 83, type: !28)
!2304 = !DILocation(line: 83, column: 23, scope: !439)
!2305 = !DILocalVariable(name: "prices", scope: !439, file: !1, line: 84, type: !99)
!2306 = !DILocation(line: 84, column: 12, scope: !439)
!2307 = !DILocalVariable(name: "i", scope: !439, file: !1, line: 85, type: !28)
!2308 = !DILocation(line: 85, column: 11, scope: !439)
!2309 = !DILocalVariable(name: "table_size", scope: !439, file: !1, line: 87, type: !433)
!2310 = !DILocation(line: 87, column: 17, scope: !439)
!2311 = !DILocation(line: 87, column: 30, scope: !439)
!2312 = !DILocation(line: 87, column: 34, scope: !439)
!2313 = !DILocation(line: 88, column: 28, scope: !439)
!2314 = !DILocation(line: 88, column: 15, scope: !439)
!2315 = !DILocation(line: 88, column: 2, scope: !439)
!2316 = !DILocation(line: 88, column: 6, scope: !439)
!2317 = !DILocation(line: 88, column: 26, scope: !439)
!2318 = !DILocation(line: 90, column: 22, scope: !439)
!2319 = !DILocation(line: 90, column: 26, scope: !439)
!2320 = !DILocation(line: 90, column: 7, scope: !439)
!2321 = !DILocation(line: 90, column: 5, scope: !439)
!2322 = !DILocation(line: 91, column: 22, scope: !439)
!2323 = !DILocation(line: 91, column: 26, scope: !439)
!2324 = !DILocation(line: 91, column: 7, scope: !439)
!2325 = !DILocation(line: 91, column: 5, scope: !439)
!2326 = !DILocation(line: 92, column: 7, scope: !439)
!2327 = !DILocation(line: 92, column: 27, scope: !439)
!2328 = !DILocation(line: 92, column: 31, scope: !439)
!2329 = !DILocation(line: 92, column: 12, scope: !439)
!2330 = !DILocation(line: 92, column: 10, scope: !439)
!2331 = !DILocation(line: 92, column: 5, scope: !439)
!2332 = !DILocation(line: 93, column: 7, scope: !439)
!2333 = !DILocation(line: 93, column: 27, scope: !439)
!2334 = !DILocation(line: 93, column: 31, scope: !439)
!2335 = !DILocation(line: 93, column: 12, scope: !439)
!2336 = !DILocation(line: 93, column: 10, scope: !439)
!2337 = !DILocation(line: 93, column: 5, scope: !439)
!2338 = !DILocation(line: 94, column: 22, scope: !439)
!2339 = !DILocation(line: 94, column: 11, scope: !439)
!2340 = !DILocation(line: 94, column: 15, scope: !439)
!2341 = !DILocation(line: 94, column: 9, scope: !439)
!2342 = !DILocation(line: 96, column: 9, scope: !2343)
!2343 = distinct !DILexicalBlock(scope: !439, file: !1, line: 96, column: 2)
!2344 = !DILocation(line: 96, column: 7, scope: !2343)
!2345 = !DILocation(line: 96, column: 14, scope: !2346)
!2346 = !DILexicalBlockFile(scope: !2347, file: !1, discriminator: 1)
!2347 = distinct !DILexicalBlock(scope: !2343, file: !1, line: 96, column: 2)
!2348 = !DILocation(line: 96, column: 18, scope: !2346)
!2349 = !DILocation(line: 96, column: 16, scope: !2346)
!2350 = !DILocation(line: 96, column: 29, scope: !2346)
!2351 = !DILocation(line: 96, column: 32, scope: !2352)
!2352 = !DILexicalBlockFile(scope: !2347, file: !1, discriminator: 2)
!2353 = !DILocation(line: 96, column: 34, scope: !2352)
!2354 = !DILocation(line: 96, column: 2, scope: !2355)
!2355 = !DILexicalBlockFile(scope: !2343, file: !1, discriminator: 3)
!2356 = !DILocation(line: 97, column: 15, scope: !2347)
!2357 = !DILocation(line: 97, column: 45, scope: !2347)
!2358 = !DILocation(line: 97, column: 37, scope: !2347)
!2359 = !DILocation(line: 97, column: 41, scope: !2347)
!2360 = !DILocation(line: 98, column: 19, scope: !2347)
!2361 = !DILocation(line: 97, column: 20, scope: !2347)
!2362 = !DILocation(line: 97, column: 18, scope: !2347)
!2363 = !DILocation(line: 97, column: 10, scope: !2347)
!2364 = !DILocation(line: 97, column: 3, scope: !2347)
!2365 = !DILocation(line: 97, column: 13, scope: !2347)
!2366 = !DILocation(line: 96, column: 53, scope: !2367)
!2367 = !DILexicalBlockFile(scope: !2347, file: !1, discriminator: 4)
!2368 = !DILocation(line: 96, column: 2, scope: !2367)
!2369 = !DILocation(line: 100, column: 2, scope: !439)
!2370 = !DILocation(line: 100, column: 9, scope: !2371)
!2371 = !DILexicalBlockFile(scope: !2372, file: !1, discriminator: 1)
!2372 = distinct !DILexicalBlock(scope: !2373, file: !1, line: 100, column: 2)
!2373 = distinct !DILexicalBlock(scope: !439, file: !1, line: 100, column: 2)
!2374 = !DILocation(line: 100, column: 13, scope: !2371)
!2375 = !DILocation(line: 100, column: 11, scope: !2371)
!2376 = !DILocation(line: 100, column: 24, scope: !2371)
!2377 = !DILocation(line: 100, column: 27, scope: !2378)
!2378 = !DILexicalBlockFile(scope: !2372, file: !1, discriminator: 2)
!2379 = !DILocation(line: 100, column: 29, scope: !2378)
!2380 = !DILocation(line: 100, column: 2, scope: !2381)
!2381 = !DILexicalBlockFile(scope: !2373, file: !1, discriminator: 3)
!2382 = !DILocation(line: 101, column: 15, scope: !2372)
!2383 = !DILocation(line: 101, column: 45, scope: !2372)
!2384 = !DILocation(line: 101, column: 37, scope: !2372)
!2385 = !DILocation(line: 101, column: 41, scope: !2372)
!2386 = !DILocation(line: 102, column: 19, scope: !2372)
!2387 = !DILocation(line: 102, column: 21, scope: !2372)
!2388 = !DILocation(line: 101, column: 20, scope: !2372)
!2389 = !DILocation(line: 101, column: 18, scope: !2372)
!2390 = !DILocation(line: 101, column: 10, scope: !2372)
!2391 = !DILocation(line: 101, column: 3, scope: !2372)
!2392 = !DILocation(line: 101, column: 13, scope: !2372)
!2393 = !DILocation(line: 100, column: 66, scope: !2394)
!2394 = !DILexicalBlockFile(scope: !2372, file: !1, discriminator: 4)
!2395 = !DILocation(line: 100, column: 2, scope: !2394)
!2396 = !DILocation(line: 104, column: 2, scope: !439)
!2397 = !DILocation(line: 104, column: 9, scope: !2398)
!2398 = !DILexicalBlockFile(scope: !2399, file: !1, discriminator: 1)
!2399 = distinct !DILexicalBlock(scope: !2400, file: !1, line: 104, column: 2)
!2400 = distinct !DILexicalBlock(scope: !439, file: !1, line: 104, column: 2)
!2401 = !DILocation(line: 104, column: 13, scope: !2398)
!2402 = !DILocation(line: 104, column: 11, scope: !2398)
!2403 = !DILocation(line: 104, column: 2, scope: !2398)
!2404 = !DILocation(line: 105, column: 15, scope: !2399)
!2405 = !DILocation(line: 105, column: 37, scope: !2399)
!2406 = !DILocation(line: 105, column: 41, scope: !2399)
!2407 = !DILocation(line: 106, column: 5, scope: !2399)
!2408 = !DILocation(line: 106, column: 7, scope: !2399)
!2409 = !DILocation(line: 106, column: 25, scope: !2399)
!2410 = !DILocation(line: 105, column: 20, scope: !2399)
!2411 = !DILocation(line: 105, column: 18, scope: !2399)
!2412 = !DILocation(line: 105, column: 10, scope: !2399)
!2413 = !DILocation(line: 105, column: 3, scope: !2399)
!2414 = !DILocation(line: 105, column: 13, scope: !2399)
!2415 = !DILocation(line: 104, column: 25, scope: !2416)
!2416 = !DILexicalBlockFile(scope: !2399, file: !1, discriminator: 2)
!2417 = !DILocation(line: 104, column: 2, scope: !2416)
!2418 = !DILocation(line: 108, column: 2, scope: !439)
!2419 = !DILocalVariable(name: "prob", arg: 1, scope: !442, file: !443, line: 37, type: !446)
!2420 = !DILocation(line: 37, column: 34, scope: !442)
!2421 = !DILocation(line: 39, column: 24, scope: !442)
!2422 = !DILocation(line: 39, column: 29, scope: !442)
!2423 = !DILocation(line: 39, column: 9, scope: !442)
!2424 = !DILocation(line: 39, column: 2, scope: !442)
!2425 = !DILocalVariable(name: "prob", arg: 1, scope: !447, file: !443, line: 44, type: !446)
!2426 = !DILocation(line: 44, column: 34, scope: !447)
!2427 = !DILocation(line: 46, column: 25, scope: !447)
!2428 = !DILocation(line: 46, column: 30, scope: !447)
!2429 = !DILocation(line: 47, column: 4, scope: !447)
!2430 = !DILocation(line: 46, column: 9, scope: !447)
!2431 = !DILocation(line: 46, column: 2, scope: !447)
!2432 = !DILocalVariable(name: "probs", arg: 1, scope: !448, file: !443, line: 52, type: !451)
!2433 = !DILocation(line: 52, column: 43, scope: !448)
!2434 = !DILocalVariable(name: "bit_levels", arg: 2, scope: !448, file: !443, line: 53, type: !433)
!2435 = !DILocation(line: 53, column: 18, scope: !448)
!2436 = !DILocalVariable(name: "symbol", arg: 3, scope: !448, file: !443, line: 53, type: !28)
!2437 = !DILocation(line: 53, column: 39, scope: !448)
!2438 = !DILocalVariable(name: "price", scope: !448, file: !443, line: 55, type: !28)
!2439 = !DILocation(line: 55, column: 11, scope: !448)
!2440 = !DILocation(line: 56, column: 27, scope: !448)
!2441 = !DILocation(line: 56, column: 24, scope: !448)
!2442 = !DILocation(line: 56, column: 9, scope: !448)
!2443 = !DILocation(line: 58, column: 2, scope: !448)
!2444 = !DILocalVariable(name: "bit", scope: !2445, file: !443, line: 59, type: !433)
!2445 = distinct !DILexicalBlock(scope: !448, file: !443, line: 58, column: 5)
!2446 = !DILocation(line: 59, column: 18, scope: !2445)
!2447 = !DILocation(line: 59, column: 24, scope: !2445)
!2448 = !DILocation(line: 59, column: 31, scope: !2445)
!2449 = !DILocation(line: 60, column: 10, scope: !2445)
!2450 = !DILocation(line: 61, column: 31, scope: !2445)
!2451 = !DILocation(line: 61, column: 25, scope: !2445)
!2452 = !DILocation(line: 61, column: 40, scope: !2445)
!2453 = !DILocation(line: 61, column: 12, scope: !2445)
!2454 = !DILocation(line: 61, column: 9, scope: !2445)
!2455 = !DILocation(line: 62, column: 2, scope: !2445)
!2456 = !DILocation(line: 62, column: 11, scope: !2457)
!2457 = !DILexicalBlockFile(scope: !448, file: !443, discriminator: 1)
!2458 = !DILocation(line: 62, column: 18, scope: !2457)
!2459 = !DILocation(line: 62, column: 2, scope: !2457)
!2460 = !DILocation(line: 64, column: 9, scope: !448)
!2461 = !DILocation(line: 64, column: 2, scope: !448)
!2462 = !DILocalVariable(name: "prob", arg: 1, scope: !453, file: !443, line: 29, type: !446)
!2463 = !DILocation(line: 29, column: 32, scope: !453)
!2464 = !DILocalVariable(name: "bit", arg: 2, scope: !453, file: !443, line: 29, type: !433)
!2465 = !DILocation(line: 29, column: 53, scope: !453)
!2466 = !DILocation(line: 31, column: 25, scope: !453)
!2467 = !DILocation(line: 31, column: 48, scope: !453)
!2468 = !DILocation(line: 31, column: 46, scope: !453)
!2469 = !DILocation(line: 32, column: 4, scope: !453)
!2470 = !DILocation(line: 31, column: 30, scope: !453)
!2471 = !DILocation(line: 32, column: 33, scope: !453)
!2472 = !DILocation(line: 31, column: 9, scope: !453)
!2473 = !DILocation(line: 31, column: 2, scope: !453)
!2474 = !DILocalVariable(name: "pos", arg: 1, scope: !457, file: !458, line: 110, type: !28)
!2475 = !DILocation(line: 110, column: 23, scope: !457)
!2476 = !DILocation(line: 114, column: 6, scope: !2477)
!2477 = distinct !DILexicalBlock(scope: !457, file: !458, line: 114, column: 6)
!2478 = !DILocation(line: 114, column: 10, scope: !2477)
!2479 = !DILocation(line: 114, column: 6, scope: !457)
!2480 = !DILocation(line: 115, column: 23, scope: !2477)
!2481 = !DILocation(line: 115, column: 10, scope: !2477)
!2482 = !DILocation(line: 115, column: 3, scope: !2477)
!2483 = !DILocation(line: 117, column: 6, scope: !2484)
!2484 = distinct !DILexicalBlock(scope: !457, file: !458, line: 117, column: 6)
!2485 = !DILocation(line: 117, column: 10, scope: !2484)
!2486 = !DILocation(line: 117, column: 6, scope: !457)
!2487 = !DILocation(line: 118, column: 10, scope: !2484)
!2488 = !DILocation(line: 118, column: 3, scope: !2484)
!2489 = !DILocation(line: 120, column: 9, scope: !457)
!2490 = !DILocation(line: 120, column: 2, scope: !457)
!2491 = !DILocation(line: 121, column: 1, scope: !457)
!2492 = !DILocalVariable(name: "rc", arg: 1, scope: !461, file: !19, line: 90, type: !405)
!2493 = !DILocation(line: 90, column: 40, scope: !461)
!2494 = !DILocalVariable(name: "probs", arg: 2, scope: !461, file: !19, line: 90, type: !43)
!2495 = !DILocation(line: 90, column: 57, scope: !461)
!2496 = !DILocalVariable(name: "bit_count", arg: 3, scope: !461, file: !19, line: 91, type: !28)
!2497 = !DILocation(line: 91, column: 12, scope: !461)
!2498 = !DILocalVariable(name: "symbol", arg: 4, scope: !461, file: !19, line: 91, type: !28)
!2499 = !DILocation(line: 91, column: 32, scope: !461)
!2500 = !DILocalVariable(name: "model_index", scope: !461, file: !19, line: 93, type: !28)
!2501 = !DILocation(line: 93, column: 11, scope: !461)
!2502 = !DILocation(line: 95, column: 2, scope: !461)
!2503 = !DILocalVariable(name: "bit", scope: !2504, file: !19, line: 96, type: !433)
!2504 = distinct !DILexicalBlock(scope: !461, file: !19, line: 95, column: 5)
!2505 = !DILocation(line: 96, column: 18, scope: !2504)
!2506 = !DILocation(line: 96, column: 24, scope: !2504)
!2507 = !DILocation(line: 96, column: 31, scope: !2504)
!2508 = !DILocation(line: 97, column: 10, scope: !2504)
!2509 = !DILocation(line: 98, column: 10, scope: !2504)
!2510 = !DILocation(line: 98, column: 21, scope: !2504)
!2511 = !DILocation(line: 98, column: 15, scope: !2504)
!2512 = !DILocation(line: 98, column: 35, scope: !2504)
!2513 = !DILocation(line: 98, column: 3, scope: !2504)
!2514 = !DILocation(line: 99, column: 18, scope: !2504)
!2515 = !DILocation(line: 99, column: 30, scope: !2504)
!2516 = !DILocation(line: 99, column: 38, scope: !2504)
!2517 = !DILocation(line: 99, column: 36, scope: !2504)
!2518 = !DILocation(line: 99, column: 15, scope: !2504)
!2519 = !DILocation(line: 100, column: 2, scope: !2504)
!2520 = !DILocation(line: 100, column: 11, scope: !2521)
!2521 = !DILexicalBlockFile(scope: !461, file: !19, discriminator: 1)
!2522 = !DILocation(line: 100, column: 23, scope: !2521)
!2523 = !DILocation(line: 100, column: 2, scope: !2521)
!2524 = !DILocation(line: 101, column: 1, scope: !461)
!2525 = !DILocalVariable(name: "rc", arg: 1, scope: !462, file: !19, line: 105, type: !405)
!2526 = !DILocation(line: 105, column: 31, scope: !462)
!2527 = !DILocalVariable(name: "value", arg: 2, scope: !462, file: !19, line: 106, type: !28)
!2528 = !DILocation(line: 106, column: 12, scope: !462)
!2529 = !DILocalVariable(name: "bit_count", arg: 3, scope: !462, file: !19, line: 106, type: !28)
!2530 = !DILocation(line: 106, column: 28, scope: !462)
!2531 = !DILocation(line: 108, column: 2, scope: !462)
!2532 = !DILocation(line: 110, column: 23, scope: !2533)
!2533 = distinct !DILexicalBlock(scope: !462, file: !19, line: 108, column: 5)
!2534 = !DILocation(line: 110, column: 32, scope: !2533)
!2535 = !DILocation(line: 110, column: 29, scope: !2533)
!2536 = !DILocation(line: 110, column: 45, scope: !2533)
!2537 = !DILocation(line: 110, column: 19, scope: !2533)
!2538 = !DILocation(line: 109, column: 15, scope: !2533)
!2539 = !DILocation(line: 109, column: 19, scope: !2533)
!2540 = !DILocation(line: 109, column: 24, scope: !2533)
!2541 = !DILocation(line: 109, column: 3, scope: !2533)
!2542 = !DILocation(line: 109, column: 7, scope: !2533)
!2543 = !DILocation(line: 110, column: 5, scope: !2533)
!2544 = !DILocation(line: 111, column: 2, scope: !2533)
!2545 = !DILocation(line: 111, column: 11, scope: !2546)
!2546 = !DILexicalBlockFile(scope: !462, file: !19, discriminator: 1)
!2547 = !DILocation(line: 111, column: 21, scope: !2546)
!2548 = !DILocation(line: 111, column: 2, scope: !2546)
!2549 = !DILocation(line: 112, column: 1, scope: !462)
!2550 = !DILocalVariable(name: "coder", arg: 1, scope: !504, file: !1, line: 417, type: !105)
!2551 = !DILocation(line: 417, column: 39, scope: !504)
!2552 = !DILocalVariable(name: "mf", arg: 2, scope: !504, file: !1, line: 417, type: !217)
!2553 = !DILocation(line: 417, column: 69, scope: !504)
!2554 = !DILocalVariable(name: "out", arg: 3, scope: !504, file: !1, line: 418, type: !254)
!2555 = !DILocation(line: 418, column: 26, scope: !504)
!2556 = !DILocalVariable(name: "out_pos", arg: 4, scope: !504, file: !1, line: 418, type: !255)
!2557 = !DILocation(line: 418, column: 53, scope: !504)
!2558 = !DILocalVariable(name: "out_size", arg: 5, scope: !504, file: !1, line: 419, type: !34)
!2559 = !DILocation(line: 419, column: 10, scope: !504)
!2560 = !DILocation(line: 422, column: 6, scope: !2561)
!2561 = distinct !DILexicalBlock(scope: !504, file: !1, line: 422, column: 6)
!2562 = !DILocation(line: 422, column: 6, scope: !504)
!2563 = !DILocation(line: 423, column: 3, scope: !2561)
!2564 = !DILocation(line: 425, column: 26, scope: !504)
!2565 = !DILocation(line: 425, column: 33, scope: !504)
!2566 = !DILocation(line: 425, column: 37, scope: !504)
!2567 = !DILocation(line: 425, column: 42, scope: !504)
!2568 = !DILocation(line: 425, column: 51, scope: !504)
!2569 = !DILocation(line: 425, column: 9, scope: !504)
!2570 = !DILocation(line: 425, column: 2, scope: !504)
!2571 = !DILocation(line: 426, column: 1, scope: !504)
