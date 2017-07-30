; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/auto_decoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type { %struct.lzma_next_coder_s, i64, i32, i32 }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_stream = type { i8*, i64, i64, i8*, i64, i64, %struct.lzma_allocator*, %struct.lzma_internal_s*, i8*, i8*, i8*, i8*, i64, i64, i64, i64, i32, i32 }
%struct.lzma_internal_s = type { %struct.lzma_next_coder_s, i32, i64, [4 x i8], i8 }

@LZMA_NEXT_CODER_INIT = internal constant %struct.lzma_next_coder_s { %struct.lzma_coder_s* null, i64 -1, i64 0, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* null, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* null, i32 (%struct.lzma_coder_s*)* null, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)* null, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* null }, align 8
@.str = private unnamed_addr constant [2 x i8] c"0\00", align 1
@.str.1 = private unnamed_addr constant [84 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/auto_decoder.c\00", align 1
@__PRETTY_FUNCTION__.auto_decode = private unnamed_addr constant [162 x i8] c"lzma_ret auto_decode(lzma_coder *, lzma_allocator *, const uint8_t *restrict, size_t *restrict, size_t, uint8_t *restrict, size_t *restrict, size_t, lzma_action)\00", align 1
@.str.2 = private unnamed_addr constant [33 x i8] c"*old_memlimit == coder->memlimit\00", align 1
@__PRETTY_FUNCTION__.auto_decoder_memconfig = private unnamed_addr constant [80 x i8] c"lzma_ret auto_decoder_memconfig(lzma_coder *, uint64_t *, uint64_t *, uint64_t)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @lzma_auto_decoder(%struct.lzma_stream* %strm, i64 %memlimit, i32 %flags) #0 !dbg !144 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.lzma_stream*, align 8
  %memlimit.addr = alloca i64, align 8
  %flags.addr = alloca i32, align 4
  %ret_ = alloca i32, align 4
  %ret_2 = alloca i32, align 4
  store %struct.lzma_stream* %strm, %struct.lzma_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream** %strm.addr, metadata !187, metadata !188), !dbg !189
  store i64 %memlimit, i64* %memlimit.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %memlimit.addr, metadata !190, metadata !188), !dbg !191
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !192, metadata !188), !dbg !193
  br label %do.body, !dbg !194

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !195, metadata !188), !dbg !197
  br label %do.body1, !dbg !198

do.body1:                                         ; preds = %do.body
  call void @llvm.dbg.declare(metadata i32* %ret_2, metadata !200, metadata !188), !dbg !203
  %0 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !204
  %call = call i32 @lzma_strm_init(%struct.lzma_stream* %0), !dbg !204
  store i32 %call, i32* %ret_2, align 4, !dbg !204
  %1 = load i32, i32* %ret_2, align 4, !dbg !204
  %cmp = icmp ne i32 %1, 0, !dbg !204
  br i1 %cmp, label %if.then, label %if.end, !dbg !204

if.then:                                          ; preds = %do.body1
  %2 = load i32, i32* %ret_2, align 4, !dbg !206
  store i32 %2, i32* %retval, align 4, !dbg !206
  br label %return, !dbg !206

if.end:                                           ; preds = %do.body1
  br label %do.end, !dbg !209

do.end:                                           ; preds = %if.end
  %3 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !211
  %internal = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %3, i32 0, i32 7, !dbg !211
  %4 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal, align 8, !dbg !211
  %next = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %4, i32 0, i32 0, !dbg !211
  %5 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !211
  %allocator = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %5, i32 0, i32 6, !dbg !211
  %6 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator, align 8, !dbg !211
  %7 = load i64, i64* %memlimit.addr, align 8, !dbg !211
  %8 = load i32, i32* %flags.addr, align 4, !dbg !211
  %call3 = call i32 @auto_decoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %6, i64 %7, i32 %8), !dbg !211
  store i32 %call3, i32* %ret_, align 4, !dbg !211
  %9 = load i32, i32* %ret_, align 4, !dbg !211
  %cmp4 = icmp ne i32 %9, 0, !dbg !211
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !211

if.then5:                                         ; preds = %do.end
  %10 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !213
  call void @lzma_end(%struct.lzma_stream* %10) #6, !dbg !213
  %11 = load i32, i32* %ret_, align 4, !dbg !213
  store i32 %11, i32* %retval, align 4, !dbg !213
  br label %return, !dbg !213

if.end6:                                          ; preds = %do.end
  br label %do.end7, !dbg !217

do.end7:                                          ; preds = %if.end6
  %12 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !219
  %internal8 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %12, i32 0, i32 7, !dbg !220
  %13 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal8, align 8, !dbg !220
  %supported_actions = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %13, i32 0, i32 3, !dbg !221
  %arrayidx = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions, i64 0, i64 0, !dbg !219
  store i8 1, i8* %arrayidx, align 8, !dbg !222
  %14 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !223
  %internal9 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %14, i32 0, i32 7, !dbg !224
  %15 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal9, align 8, !dbg !224
  %supported_actions10 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %15, i32 0, i32 3, !dbg !225
  %arrayidx11 = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions10, i64 0, i64 3, !dbg !223
  store i8 1, i8* %arrayidx11, align 1, !dbg !226
  store i32 0, i32* %retval, align 4, !dbg !227
  br label %return, !dbg !227

return:                                           ; preds = %do.end7, %if.then5, %if.then
  %16 = load i32, i32* %retval, align 4, !dbg !228
  ret i32 %16, !dbg !228
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @lzma_strm_init(%struct.lzma_stream*) #2

; Function Attrs: nounwind uwtable
define internal i32 @auto_decoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, i64 %memlimit, i32 %flags) #0 !dbg !173 {
entry:
  %retval = alloca i32, align 4
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %memlimit.addr = alloca i64, align 8
  %flags.addr = alloca i32, align 4
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !229, metadata !188), !dbg !230
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !231, metadata !188), !dbg !232
  store i64 %memlimit, i64* %memlimit.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %memlimit.addr, metadata !233, metadata !188), !dbg !234
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !235, metadata !188), !dbg !236
  br label %do.body, !dbg !237

do.body:                                          ; preds = %entry
  %0 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !238
  %init = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %0, i32 0, i32 2, !dbg !238
  %1 = load i64, i64* %init, align 8, !dbg !238
  %cmp = icmp ne i64 ptrtoint (i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, i64, i32)* @auto_decoder_init to i64), %1, !dbg !238
  br i1 %cmp, label %if.then, label %if.end, !dbg !238

if.then:                                          ; preds = %do.body
  %2 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !242
  %3 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !242
  call void @lzma_next_end(%struct.lzma_next_coder_s* %2, %struct.lzma_allocator* %3), !dbg !242
  br label %if.end, !dbg !242

if.end:                                           ; preds = %if.then, %do.body
  %4 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !244
  %init1 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %4, i32 0, i32 2, !dbg !244
  store i64 ptrtoint (i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, i64, i32)* @auto_decoder_init to i64), i64* %init1, align 8, !dbg !244
  br label %do.end, !dbg !244

do.end:                                           ; preds = %if.end
  %5 = load i64, i64* %memlimit.addr, align 8, !dbg !246
  %cmp2 = icmp eq i64 %5, 0, !dbg !248
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !249

if.then3:                                         ; preds = %do.end
  store i32 11, i32* %retval, align 4, !dbg !250
  br label %return, !dbg !250

if.end4:                                          ; preds = %do.end
  %6 = load i32, i32* %flags.addr, align 4, !dbg !251
  %and = and i32 %6, -16, !dbg !253
  %tobool = icmp ne i32 %and, 0, !dbg !253
  br i1 %tobool, label %if.then5, label %if.end6, !dbg !254

if.then5:                                         ; preds = %if.end4
  store i32 8, i32* %retval, align 4, !dbg !255
  br label %return, !dbg !255

if.end6:                                          ; preds = %if.end4
  %7 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !256
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %7, i32 0, i32 0, !dbg !258
  %8 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !258
  %cmp7 = icmp eq %struct.lzma_coder_s* %8, null, !dbg !259
  br i1 %cmp7, label %if.then8, label %if.end16, !dbg !260

if.then8:                                         ; preds = %if.end6
  %9 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !261
  %call = call noalias i8* @lzma_alloc(i64 80, %struct.lzma_allocator* %9), !dbg !263
  %10 = bitcast i8* %call to %struct.lzma_coder_s*, !dbg !263
  %11 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !264
  %coder9 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %11, i32 0, i32 0, !dbg !265
  store %struct.lzma_coder_s* %10, %struct.lzma_coder_s** %coder9, align 8, !dbg !266
  %12 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !267
  %coder10 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %12, i32 0, i32 0, !dbg !269
  %13 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder10, align 8, !dbg !269
  %cmp11 = icmp eq %struct.lzma_coder_s* %13, null, !dbg !270
  br i1 %cmp11, label %if.then12, label %if.end13, !dbg !271

if.then12:                                        ; preds = %if.then8
  store i32 5, i32* %retval, align 4, !dbg !272
  br label %return, !dbg !272

if.end13:                                         ; preds = %if.then8
  %14 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !273
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %14, i32 0, i32 3, !dbg !274
  store i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* @auto_decode, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !275
  %15 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !276
  %end = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %15, i32 0, i32 4, !dbg !277
  store void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* @auto_decoder_end, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)** %end, align 8, !dbg !278
  %16 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !279
  %get_check = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %16, i32 0, i32 5, !dbg !280
  store i32 (%struct.lzma_coder_s*)* @auto_decoder_get_check, i32 (%struct.lzma_coder_s*)** %get_check, align 8, !dbg !281
  %17 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !282
  %memconfig = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %17, i32 0, i32 6, !dbg !283
  store i32 (%struct.lzma_coder_s*, i64*, i64*, i64)* @auto_decoder_memconfig, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)** %memconfig, align 8, !dbg !284
  %18 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !285
  %coder14 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %18, i32 0, i32 0, !dbg !286
  %19 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder14, align 8, !dbg !286
  %next15 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %19, i32 0, i32 0, !dbg !287
  %20 = bitcast %struct.lzma_next_coder_s* %next15 to i8*, !dbg !288
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %20, i8* bitcast (%struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT to i8*), i64 64, i32 8, i1 false), !dbg !288
  br label %if.end16, !dbg !289

if.end16:                                         ; preds = %if.end13, %if.end6
  %21 = load i64, i64* %memlimit.addr, align 8, !dbg !290
  %22 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !291
  %coder17 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %22, i32 0, i32 0, !dbg !292
  %23 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder17, align 8, !dbg !292
  %memlimit18 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %23, i32 0, i32 1, !dbg !293
  store i64 %21, i64* %memlimit18, align 8, !dbg !294
  %24 = load i32, i32* %flags.addr, align 4, !dbg !295
  %25 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !296
  %coder19 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %25, i32 0, i32 0, !dbg !297
  %26 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder19, align 8, !dbg !297
  %flags20 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %26, i32 0, i32 2, !dbg !298
  store i32 %24, i32* %flags20, align 8, !dbg !299
  %27 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !300
  %coder21 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %27, i32 0, i32 0, !dbg !301
  %28 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder21, align 8, !dbg !301
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %28, i32 0, i32 3, !dbg !302
  store i32 0, i32* %sequence, align 4, !dbg !303
  store i32 0, i32* %retval, align 4, !dbg !304
  br label %return, !dbg !304

return:                                           ; preds = %if.end16, %if.then12, %if.then5, %if.then3
  %29 = load i32, i32* %retval, align 4, !dbg !305
  ret i32 %29, !dbg !305
}

; Function Attrs: nounwind
declare void @lzma_end(%struct.lzma_stream*) #3

declare void @lzma_next_end(%struct.lzma_next_coder_s*, %struct.lzma_allocator*) #2

declare noalias i8* @lzma_alloc(i64, %struct.lzma_allocator*) #2

; Function Attrs: nounwind uwtable
define internal i32 @auto_decode(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator, i8* noalias %in, i64* noalias %in_pos, i64 %in_size, i8* noalias %out, i64* noalias %out_pos, i64 %out_size, i32 %action) #0 !dbg !177 {
entry:
  %retval = alloca i32, align 4
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %in.addr = alloca i8*, align 8
  %in_pos.addr = alloca i64*, align 8
  %in_size.addr = alloca i64, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  %action.addr = alloca i32, align 4
  %ret_ = alloca i32, align 4
  %ret_10 = alloca i32, align 4
  %ret = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !306, metadata !188), !dbg !307
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !308, metadata !188), !dbg !309
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !310, metadata !188), !dbg !311
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !312, metadata !188), !dbg !313
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !314, metadata !188), !dbg !315
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !316, metadata !188), !dbg !317
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !318, metadata !188), !dbg !319
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !320, metadata !188), !dbg !321
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !322, metadata !188), !dbg !323
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !324
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 3, !dbg !325
  %1 = load i32, i32* %sequence, align 4, !dbg !325
  switch i32 %1, label %sw.default [
    i32 0, label %sw.bb
    i32 1, label %sw.bb28
    i32 2, label %sw.bb42
  ], !dbg !326

sw.bb:                                            ; preds = %entry
  %2 = load i64*, i64** %in_pos.addr, align 8, !dbg !327
  %3 = load i64, i64* %2, align 8, !dbg !330
  %4 = load i64, i64* %in_size.addr, align 8, !dbg !331
  %cmp = icmp uge i64 %3, %4, !dbg !332
  br i1 %cmp, label %if.then, label %if.end, !dbg !333

if.then:                                          ; preds = %sw.bb
  store i32 0, i32* %retval, align 4, !dbg !334
  br label %return, !dbg !334

if.end:                                           ; preds = %sw.bb
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !335
  %sequence1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 3, !dbg !336
  store i32 1, i32* %sequence1, align 4, !dbg !337
  %6 = load i64*, i64** %in_pos.addr, align 8, !dbg !338
  %7 = load i64, i64* %6, align 8, !dbg !340
  %8 = load i8*, i8** %in.addr, align 8, !dbg !341
  %arrayidx = getelementptr inbounds i8, i8* %8, i64 %7, !dbg !341
  %9 = load i8, i8* %arrayidx, align 1, !dbg !341
  %conv = zext i8 %9 to i32, !dbg !341
  %cmp2 = icmp eq i32 %conv, 253, !dbg !342
  br i1 %cmp2, label %if.then4, label %if.else, !dbg !343

if.then4:                                         ; preds = %if.end
  br label %do.body, !dbg !344

do.body:                                          ; preds = %if.then4
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !346, metadata !188), !dbg !348
  %10 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !349
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %10, i32 0, i32 0, !dbg !349
  %11 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !349
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !349
  %memlimit = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %12, i32 0, i32 1, !dbg !349
  %13 = load i64, i64* %memlimit, align 8, !dbg !349
  %14 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !349
  %flags = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %14, i32 0, i32 2, !dbg !349
  %15 = load i32, i32* %flags, align 8, !dbg !349
  %call = call i32 @lzma_stream_decoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %11, i64 %13, i32 %15), !dbg !349
  store i32 %call, i32* %ret_, align 4, !dbg !349
  %16 = load i32, i32* %ret_, align 4, !dbg !349
  %cmp5 = icmp ne i32 %16, 0, !dbg !349
  br i1 %cmp5, label %if.then7, label %if.end8, !dbg !349

if.then7:                                         ; preds = %do.body
  %17 = load i32, i32* %ret_, align 4, !dbg !351
  store i32 %17, i32* %retval, align 4, !dbg !351
  br label %return, !dbg !351

if.end8:                                          ; preds = %do.body
  br label %do.end, !dbg !354

do.end:                                           ; preds = %if.end8
  br label %if.end27, !dbg !356

if.else:                                          ; preds = %if.end
  br label %do.body9, !dbg !357

do.body9:                                         ; preds = %if.else
  call void @llvm.dbg.declare(metadata i32* %ret_10, metadata !359, metadata !188), !dbg !361
  %18 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !362
  %next11 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %18, i32 0, i32 0, !dbg !362
  %19 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !362
  %20 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !362
  %memlimit12 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %20, i32 0, i32 1, !dbg !362
  %21 = load i64, i64* %memlimit12, align 8, !dbg !362
  %call13 = call i32 @lzma_alone_decoder_init(%struct.lzma_next_coder_s* %next11, %struct.lzma_allocator* %19, i64 %21, i1 zeroext true), !dbg !362
  store i32 %call13, i32* %ret_10, align 4, !dbg !362
  %22 = load i32, i32* %ret_10, align 4, !dbg !362
  %cmp14 = icmp ne i32 %22, 0, !dbg !362
  br i1 %cmp14, label %if.then16, label %if.end17, !dbg !362

if.then16:                                        ; preds = %do.body9
  %23 = load i32, i32* %ret_10, align 4, !dbg !364
  store i32 %23, i32* %retval, align 4, !dbg !364
  br label %return, !dbg !364

if.end17:                                         ; preds = %do.body9
  br label %do.end18, !dbg !367

do.end18:                                         ; preds = %if.end17
  %24 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !369
  %flags19 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %24, i32 0, i32 2, !dbg !371
  %25 = load i32, i32* %flags19, align 8, !dbg !371
  %and = and i32 %25, 1, !dbg !372
  %tobool = icmp ne i32 %and, 0, !dbg !372
  br i1 %tobool, label %if.then20, label %if.end21, !dbg !373

if.then20:                                        ; preds = %do.end18
  store i32 2, i32* %retval, align 4, !dbg !374
  br label %return, !dbg !374

if.end21:                                         ; preds = %do.end18
  %26 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !375
  %flags22 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %26, i32 0, i32 2, !dbg !377
  %27 = load i32, i32* %flags22, align 8, !dbg !377
  %and23 = and i32 %27, 4, !dbg !378
  %tobool24 = icmp ne i32 %and23, 0, !dbg !378
  br i1 %tobool24, label %if.then25, label %if.end26, !dbg !379

if.then25:                                        ; preds = %if.end21
  store i32 4, i32* %retval, align 4, !dbg !380
  br label %return, !dbg !380

if.end26:                                         ; preds = %if.end21
  br label %if.end27

if.end27:                                         ; preds = %if.end26, %do.end
  br label %sw.bb28, !dbg !381

sw.bb28:                                          ; preds = %entry, %if.end27
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !383, metadata !188), !dbg !385
  %28 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !386
  %next29 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %28, i32 0, i32 0, !dbg !387
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next29, i32 0, i32 3, !dbg !388
  %29 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !388
  %30 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !389
  %next30 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %30, i32 0, i32 0, !dbg !390
  %coder31 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next30, i32 0, i32 0, !dbg !391
  %31 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder31, align 8, !dbg !391
  %32 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !392
  %33 = load i8*, i8** %in.addr, align 8, !dbg !393
  %34 = load i64*, i64** %in_pos.addr, align 8, !dbg !394
  %35 = load i64, i64* %in_size.addr, align 8, !dbg !395
  %36 = load i8*, i8** %out.addr, align 8, !dbg !396
  %37 = load i64*, i64** %out_pos.addr, align 8, !dbg !397
  %38 = load i64, i64* %out_size.addr, align 8, !dbg !398
  %39 = load i32, i32* %action.addr, align 4, !dbg !399
  %call32 = call i32 %29(%struct.lzma_coder_s* %31, %struct.lzma_allocator* %32, i8* %33, i64* %34, i64 %35, i8* %36, i64* %37, i64 %38, i32 %39), !dbg !386
  store i32 %call32, i32* %ret, align 4, !dbg !385
  %40 = load i32, i32* %ret, align 4, !dbg !400
  %cmp33 = icmp ne i32 %40, 1, !dbg !402
  br i1 %cmp33, label %if.then39, label %lor.lhs.false, !dbg !403

lor.lhs.false:                                    ; preds = %sw.bb28
  %41 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !404
  %flags35 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %41, i32 0, i32 2, !dbg !406
  %42 = load i32, i32* %flags35, align 8, !dbg !406
  %and36 = and i32 %42, 8, !dbg !407
  %cmp37 = icmp eq i32 %and36, 0, !dbg !408
  br i1 %cmp37, label %if.then39, label %if.end40, !dbg !409

if.then39:                                        ; preds = %lor.lhs.false, %sw.bb28
  %43 = load i32, i32* %ret, align 4, !dbg !411
  store i32 %43, i32* %retval, align 4, !dbg !412
  br label %return, !dbg !412

if.end40:                                         ; preds = %lor.lhs.false
  %44 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !413
  %sequence41 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %44, i32 0, i32 3, !dbg !414
  store i32 2, i32* %sequence41, align 4, !dbg !415
  br label %sw.bb42, !dbg !416

sw.bb42:                                          ; preds = %entry, %if.end40
  %45 = load i64*, i64** %in_pos.addr, align 8, !dbg !417
  %46 = load i64, i64* %45, align 8, !dbg !419
  %47 = load i64, i64* %in_size.addr, align 8, !dbg !420
  %cmp43 = icmp ult i64 %46, %47, !dbg !421
  br i1 %cmp43, label %if.then45, label %if.end46, !dbg !422

if.then45:                                        ; preds = %sw.bb42
  store i32 9, i32* %retval, align 4, !dbg !423
  br label %return, !dbg !423

if.end46:                                         ; preds = %sw.bb42
  %48 = load i32, i32* %action.addr, align 4, !dbg !424
  %cmp47 = icmp eq i32 %48, 3, !dbg !425
  %cond = select i1 %cmp47, i32 1, i32 0, !dbg !424
  store i32 %cond, i32* %retval, align 4, !dbg !426
  br label %return, !dbg !426

sw.default:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([84 x i8], [84 x i8]* @.str.1, i32 0, i32 0), i32 96, i8* getelementptr inbounds ([162 x i8], [162 x i8]* @__PRETTY_FUNCTION__.auto_decode, i32 0, i32 0)) #7, !dbg !427
  unreachable, !dbg !427

return:                                           ; preds = %if.end46, %if.then45, %if.then39, %if.then25, %if.then20, %if.then16, %if.then7, %if.then
  %49 = load i32, i32* %retval, align 4, !dbg !428
  ret i32 %49, !dbg !428
}

; Function Attrs: nounwind uwtable
define internal void @auto_decoder_end(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator) #0 !dbg !178 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !429, metadata !188), !dbg !430
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !431, metadata !188), !dbg !432
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !433
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 0, !dbg !434
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !435
  call void @lzma_next_end(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %1), !dbg !436
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !437
  %3 = bitcast %struct.lzma_coder_s* %2 to i8*, !dbg !437
  %4 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !438
  call void @lzma_free(i8* %3, %struct.lzma_allocator* %4), !dbg !439
  ret void, !dbg !440
}

; Function Attrs: nounwind uwtable
define internal i32 @auto_decoder_get_check(%struct.lzma_coder_s* %coder) #0 !dbg !179 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !441, metadata !188), !dbg !442
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !443
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 0, !dbg !444
  %get_check = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next, i32 0, i32 5, !dbg !445
  %1 = load i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*)** %get_check, align 8, !dbg !445
  %cmp = icmp eq i32 (%struct.lzma_coder_s*)* %1, null, !dbg !446
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !443

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !447

cond.false:                                       ; preds = %entry
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !449
  %next1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 0, !dbg !450
  %get_check2 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next1, i32 0, i32 5, !dbg !451
  %3 = load i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*)** %get_check2, align 8, !dbg !451
  %4 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !452
  %next3 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %4, i32 0, i32 0, !dbg !453
  %coder4 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next3, i32 0, i32 0, !dbg !454
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder4, align 8, !dbg !454
  %call = call i32 %3(%struct.lzma_coder_s* %5), !dbg !449
  br label %cond.end, !dbg !455

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ 0, %cond.true ], [ %call, %cond.false ], !dbg !457
  ret i32 %cond, !dbg !459
}

; Function Attrs: nounwind uwtable
define internal i32 @auto_decoder_memconfig(%struct.lzma_coder_s* %coder, i64* %memusage, i64* %old_memlimit, i64 %new_memlimit) #0 !dbg !180 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %memusage.addr = alloca i64*, align 8
  %old_memlimit.addr = alloca i64*, align 8
  %new_memlimit.addr = alloca i64, align 8
  %ret = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !460, metadata !188), !dbg !461
  store i64* %memusage, i64** %memusage.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %memusage.addr, metadata !462, metadata !188), !dbg !463
  store i64* %old_memlimit, i64** %old_memlimit.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %old_memlimit.addr, metadata !464, metadata !188), !dbg !465
  store i64 %new_memlimit, i64* %new_memlimit.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %new_memlimit.addr, metadata !466, metadata !188), !dbg !467
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !468, metadata !188), !dbg !469
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !470
  %next = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 0, !dbg !472
  %memconfig = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next, i32 0, i32 6, !dbg !473
  %1 = load i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)** %memconfig, align 8, !dbg !473
  %cmp = icmp ne i32 (%struct.lzma_coder_s*, i64*, i64*, i64)* %1, null, !dbg !474
  br i1 %cmp, label %if.then, label %if.else, !dbg !475

if.then:                                          ; preds = %entry
  %2 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !476
  %next1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %2, i32 0, i32 0, !dbg !478
  %memconfig2 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next1, i32 0, i32 6, !dbg !479
  %3 = load i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)** %memconfig2, align 8, !dbg !479
  %4 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !480
  %next3 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %4, i32 0, i32 0, !dbg !481
  %coder4 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next3, i32 0, i32 0, !dbg !482
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder4, align 8, !dbg !482
  %6 = load i64*, i64** %memusage.addr, align 8, !dbg !483
  %7 = load i64*, i64** %old_memlimit.addr, align 8, !dbg !484
  %8 = load i64, i64* %new_memlimit.addr, align 8, !dbg !485
  %call = call i32 %3(%struct.lzma_coder_s* %5, i64* %6, i64* %7, i64 %8), !dbg !476
  store i32 %call, i32* %ret, align 4, !dbg !486
  %9 = load i64*, i64** %old_memlimit.addr, align 8, !dbg !487
  %10 = load i64, i64* %9, align 8, !dbg !487
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !487
  %memlimit = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 1, !dbg !487
  %12 = load i64, i64* %memlimit, align 8, !dbg !487
  %cmp5 = icmp eq i64 %10, %12, !dbg !487
  br i1 %cmp5, label %cond.true, label %cond.false, !dbg !487

cond.true:                                        ; preds = %if.then
  br label %cond.end, !dbg !488

cond.false:                                       ; preds = %if.then
  call void @__assert_fail(i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([84 x i8], [84 x i8]* @.str.1, i32 0, i32 0), i32 129, i8* getelementptr inbounds ([80 x i8], [80 x i8]* @__PRETTY_FUNCTION__.auto_decoder_memconfig, i32 0, i32 0)) #7, !dbg !490
  unreachable, !dbg !490
                                                  ; No predecessors!
  br label %cond.end, !dbg !492

cond.end:                                         ; preds = %13, %cond.true
  br label %if.end, !dbg !494

if.else:                                          ; preds = %entry
  %14 = load i64*, i64** %memusage.addr, align 8, !dbg !495
  store i64 32768, i64* %14, align 8, !dbg !497
  %15 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !498
  %memlimit6 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %15, i32 0, i32 1, !dbg !499
  %16 = load i64, i64* %memlimit6, align 8, !dbg !499
  %17 = load i64*, i64** %old_memlimit.addr, align 8, !dbg !500
  store i64 %16, i64* %17, align 8, !dbg !501
  store i32 0, i32* %ret, align 4, !dbg !502
  br label %if.end

if.end:                                           ; preds = %if.else, %cond.end
  %18 = load i32, i32* %ret, align 4, !dbg !503
  %cmp7 = icmp eq i32 %18, 0, !dbg !505
  br i1 %cmp7, label %land.lhs.true, label %if.end11, !dbg !506

land.lhs.true:                                    ; preds = %if.end
  %19 = load i64, i64* %new_memlimit.addr, align 8, !dbg !507
  %cmp8 = icmp ne i64 %19, 0, !dbg !509
  br i1 %cmp8, label %if.then9, label %if.end11, !dbg !510

if.then9:                                         ; preds = %land.lhs.true
  %20 = load i64, i64* %new_memlimit.addr, align 8, !dbg !511
  %21 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !512
  %memlimit10 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %21, i32 0, i32 1, !dbg !513
  store i64 %20, i64* %memlimit10, align 8, !dbg !514
  br label %if.end11, !dbg !512

if.end11:                                         ; preds = %if.then9, %land.lhs.true, %if.end
  %22 = load i32, i32* %ret, align 4, !dbg !515
  ret i32 %22, !dbg !516
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #4

declare i32 @lzma_stream_decoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, i64, i32) #2

declare i32 @lzma_alone_decoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, i64, i1 zeroext) #2

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #5

declare void @lzma_free(i8*, %struct.lzma_allocator*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { argmemonly nounwind }
attributes #5 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind }
attributes #7 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!184, !185}
!llvm.ident = !{!186}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !142, subprograms: !143, globals: !181)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/auto_decoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !69, !86, !120, !139}
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
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !19, file: !1, line: 24, size: 32, align: 32, elements: !116)
!19 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !1, line: 17, size: 640, align: 64, elements: !20)
!20 = !{!21, !111, !112, !115}
!21 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !19, file: !1, line: 19, baseType: !22, size: 512, align: 64)
!22 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !23, line: 75, baseType: !24)
!23 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!24 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !23, line: 119, size: 512, align: 64, elements: !25)
!25 = !{!26, !29, !35, !37, !75, !80, !94, !99}
!26 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !24, file: !23, line: 121, baseType: !27, size: 64, align: 64)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!28 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !23, line: 73, baseType: !19)
!29 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !24, file: !23, line: 125, baseType: !30, size: 64, align: 64, offset: 64)
!30 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !31, line: 63, baseType: !32)
!31 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!32 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !33, line: 55, baseType: !34)
!33 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!34 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!35 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !24, file: !23, line: 131, baseType: !36, size: 64, align: 64, offset: 128)
!36 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !33, line: 122, baseType: !34)
!37 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !24, file: !23, line: 134, baseType: !38, size: 64, align: 64, offset: 192)
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !23, line: 89, baseType: !39)
!39 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !40, size: 64, align: 64)
!40 = !DISubroutineType(types: !41)
!41 = !{!42, !27, !43, !59, !64, !52, !66, !64, !52, !68}
!42 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!44 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !45)
!45 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !46)
!46 = !{!47, !54, !58}
!47 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !45, file: !4, line: 376, baseType: !48, size: 64, align: 64)
!48 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !49, size: 64, align: 64)
!49 = !DISubroutineType(types: !50)
!50 = !{!51, !51, !52, !52}
!51 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !53, line: 62, baseType: !34)
!53 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!54 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !45, file: !4, line: 390, baseType: !55, size: 64, align: 64, offset: 64)
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!56 = !DISubroutineType(types: !57)
!57 = !{null, !51, !51}
!58 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !45, file: !4, line: 401, baseType: !51, size: 64, align: 64, offset: 128)
!59 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !60)
!60 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !61, size: 64, align: 64)
!61 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !62)
!62 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !33, line: 48, baseType: !63)
!63 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!64 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !65)
!65 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !52, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !67)
!67 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64, align: 64)
!68 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !69)
!69 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 250, size: 32, align: 32, elements: !70)
!70 = !{!71, !72, !73, !74}
!71 = !DIEnumerator(name: "LZMA_RUN", value: 0)
!72 = !DIEnumerator(name: "LZMA_SYNC_FLUSH", value: 1)
!73 = !DIEnumerator(name: "LZMA_FULL_FLUSH", value: 2)
!74 = !DIEnumerator(name: "LZMA_FINISH", value: 3)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !24, file: !23, line: 139, baseType: !76, size: 64, align: 64, offset: 256)
!76 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !23, line: 97, baseType: !77)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DISubroutineType(types: !79)
!79 = !{null, !27, !43}
!80 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !24, file: !23, line: 143, baseType: !81, size: 64, align: 64, offset: 320)
!81 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!82 = !DISubroutineType(types: !83)
!83 = !{!84, !92}
!84 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !85, line: 55, baseType: !86)
!85 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!86 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !85, line: 27, size: 32, align: 32, elements: !87)
!87 = !{!88, !89, !90, !91}
!88 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!89 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!90 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!91 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!92 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !93, size: 64, align: 64)
!93 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !28)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !24, file: !23, line: 147, baseType: !95, size: 64, align: 64, offset: 384)
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !96, size: 64, align: 64)
!96 = !DISubroutineType(types: !97)
!97 = !{!42, !27, !98, !98, !32}
!98 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !32, size: 64, align: 64)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !24, file: !23, line: 152, baseType: !100, size: 64, align: 64, offset: 448)
!100 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !101, size: 64, align: 64)
!101 = !DISubroutineType(types: !102)
!102 = !{!42, !27, !43, !103, !103}
!103 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !104, size: 64, align: 64)
!104 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !105)
!105 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !106, line: 65, baseType: !107)
!106 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!107 = !DICompositeType(tag: DW_TAG_structure_type, file: !106, line: 43, size: 128, align: 64, elements: !108)
!108 = !{!109, !110}
!109 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !107, file: !106, line: 54, baseType: !30, size: 64, align: 64)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !107, file: !106, line: 63, baseType: !51, size: 64, align: 64, offset: 64)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "memlimit", scope: !19, file: !1, line: 21, baseType: !32, size: 64, align: 64, offset: 512)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !19, file: !1, line: 22, baseType: !113, size: 32, align: 32, offset: 576)
!113 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !33, line: 51, baseType: !114)
!114 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "sequence", scope: !19, file: !1, line: 28, baseType: !18, size: 32, align: 32, offset: 608)
!116 = !{!117, !118, !119}
!117 = !DIEnumerator(name: "SEQ_INIT", value: 0)
!118 = !DIEnumerator(name: "SEQ_CODE", value: 1)
!119 = !DIEnumerator(name: "SEQ_FINISH", value: 2)
!120 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !121, file: !23, line: 182, size: 32, align: 32, elements: !132)
!121 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_internal_s", file: !23, line: 174, size: 704, align: 64, elements: !122)
!122 = !{!123, !124, !125, !126, !131}
!123 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !121, file: !23, line: 176, baseType: !22, size: 512, align: 64)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "sequence", scope: !121, file: !23, line: 189, baseType: !120, size: 32, align: 32, offset: 512)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !121, file: !23, line: 194, baseType: !52, size: 64, align: 64, offset: 576)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "supported_actions", scope: !121, file: !23, line: 197, baseType: !127, size: 32, align: 8, offset: 640)
!127 = !DICompositeType(tag: DW_TAG_array_type, baseType: !128, size: 32, align: 8, elements: !129)
!128 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!129 = !{!130}
!130 = !DISubrange(count: 4)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "allow_buf_error", scope: !121, file: !23, line: 201, baseType: !128, size: 8, align: 8, offset: 672)
!132 = !{!133, !134, !135, !136, !137, !138}
!133 = !DIEnumerator(name: "ISEQ_RUN", value: 0)
!134 = !DIEnumerator(name: "ISEQ_SYNC_FLUSH", value: 1)
!135 = !DIEnumerator(name: "ISEQ_FULL_FLUSH", value: 2)
!136 = !DIEnumerator(name: "ISEQ_FINISH", value: 3)
!137 = !DIEnumerator(name: "ISEQ_END", value: 4)
!138 = !DIEnumerator(name: "ISEQ_ERROR", value: 5)
!139 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 44, size: 32, align: 32, elements: !140)
!140 = !{!141}
!141 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!142 = !{!36, !51}
!143 = !{!144, !173, !177, !178, !179, !180}
!144 = distinct !DISubprogram(name: "lzma_auto_decoder", scope: !1, file: !1, line: 178, type: !145, isLocal: false, isDefinition: true, scopeLine: 179, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!145 = !DISubroutineType(types: !146)
!146 = !{!42, !147, !32, !113}
!147 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !148, size: 64, align: 64)
!148 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_stream", file: !4, line: 490, baseType: !149)
!149 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 453, size: 1088, align: 64, elements: !150)
!150 = !{!151, !152, !153, !154, !155, !156, !157, !158, !161, !162, !163, !164, !165, !166, !167, !168, !169, !171}
!151 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !149, file: !4, line: 454, baseType: !60, size: 64, align: 64)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !149, file: !4, line: 455, baseType: !52, size: 64, align: 64, offset: 64)
!153 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !149, file: !4, line: 456, baseType: !32, size: 64, align: 64, offset: 128)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !149, file: !4, line: 458, baseType: !67, size: 64, align: 64, offset: 192)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !149, file: !4, line: 459, baseType: !52, size: 64, align: 64, offset: 256)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !149, file: !4, line: 460, baseType: !32, size: 64, align: 64, offset: 320)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "allocator", scope: !149, file: !4, line: 468, baseType: !43, size: 64, align: 64, offset: 384)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "internal", scope: !149, file: !4, line: 471, baseType: !159, size: 64, align: 64, offset: 448)
!159 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !160, size: 64, align: 64)
!160 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_internal", file: !4, line: 411, baseType: !121)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !149, file: !4, line: 479, baseType: !51, size: 64, align: 64, offset: 512)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !149, file: !4, line: 480, baseType: !51, size: 64, align: 64, offset: 576)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !149, file: !4, line: 481, baseType: !51, size: 64, align: 64, offset: 640)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr4", scope: !149, file: !4, line: 482, baseType: !51, size: 64, align: 64, offset: 704)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !149, file: !4, line: 483, baseType: !32, size: 64, align: 64, offset: 768)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !149, file: !4, line: 484, baseType: !32, size: 64, align: 64, offset: 832)
!167 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !149, file: !4, line: 485, baseType: !52, size: 64, align: 64, offset: 896)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !149, file: !4, line: 486, baseType: !52, size: 64, align: 64, offset: 960)
!169 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !149, file: !4, line: 487, baseType: !170, size: 32, align: 32, offset: 1024)
!170 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !139)
!171 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !149, file: !4, line: 488, baseType: !170, size: 32, align: 32, offset: 1056)
!172 = !{}
!173 = distinct !DISubprogram(name: "auto_decoder_init", scope: !1, file: !1, line: 146, type: !174, isLocal: true, isDefinition: true, scopeLine: 148, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!174 = !DISubroutineType(types: !175)
!175 = !{!42, !176, !43, !32, !113}
!176 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !22, size: 64, align: 64)
!177 = distinct !DISubprogram(name: "auto_decode", scope: !1, file: !1, line: 33, type: !40, isLocal: true, isDefinition: true, scopeLine: 37, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!178 = distinct !DISubprogram(name: "auto_decoder_end", scope: !1, file: !1, line: 103, type: !78, isLocal: true, isDefinition: true, scopeLine: 104, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!179 = distinct !DISubprogram(name: "auto_decoder_get_check", scope: !1, file: !1, line: 112, type: !82, isLocal: true, isDefinition: true, scopeLine: 113, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!180 = distinct !DISubprogram(name: "auto_decoder_memconfig", scope: !1, file: !1, line: 121, type: !96, isLocal: true, isDefinition: true, scopeLine: 123, flags: DIFlagPrototyped, isOptimized: false, variables: !172)
!181 = !{!182}
!182 = !DIGlobalVariable(name: "LZMA_NEXT_CODER_INIT", scope: !0, file: !23, line: 159, type: !183, isLocal: true, isDefinition: true, variable: %struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT)
!183 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !22)
!184 = !{i32 2, !"Dwarf Version", i32 4}
!185 = !{i32 2, !"Debug Info Version", i32 3}
!186 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!187 = !DILocalVariable(name: "strm", arg: 1, scope: !144, file: !1, line: 178, type: !147)
!188 = !DIExpression()
!189 = !DILocation(line: 178, column: 32, scope: !144)
!190 = !DILocalVariable(name: "memlimit", arg: 2, scope: !144, file: !1, line: 178, type: !32)
!191 = !DILocation(line: 178, column: 47, scope: !144)
!192 = !DILocalVariable(name: "flags", arg: 3, scope: !144, file: !1, line: 178, type: !113)
!193 = !DILocation(line: 178, column: 66, scope: !144)
!194 = !DILocation(line: 180, column: 2, scope: !144)
!195 = !DILocalVariable(name: "ret_", scope: !196, file: !1, line: 180, type: !42)
!196 = distinct !DILexicalBlock(scope: !144, file: !1, line: 180, column: 2)
!197 = !DILocation(line: 180, column: 2, scope: !196)
!198 = !DILocation(line: 180, column: 2, scope: !199)
!199 = !DILexicalBlockFile(scope: !196, file: !1, discriminator: 1)
!200 = !DILocalVariable(name: "ret_", scope: !201, file: !1, line: 180, type: !202)
!201 = distinct !DILexicalBlock(scope: !196, file: !1, line: 180, column: 2)
!202 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !42)
!203 = !DILocation(line: 180, column: 2, scope: !201)
!204 = !DILocation(line: 180, column: 2, scope: !205)
!205 = !DILexicalBlockFile(scope: !201, file: !1, discriminator: 2)
!206 = !DILocation(line: 180, column: 2, scope: !207)
!207 = !DILexicalBlockFile(scope: !208, file: !1, discriminator: 3)
!208 = distinct !DILexicalBlock(scope: !201, file: !1, line: 180, column: 2)
!209 = !DILocation(line: 180, column: 2, scope: !210)
!210 = !DILexicalBlockFile(scope: !201, file: !1, discriminator: 4)
!211 = !DILocation(line: 180, column: 2, scope: !212)
!212 = !DILexicalBlockFile(scope: !196, file: !1, discriminator: 5)
!213 = !DILocation(line: 180, column: 2, scope: !214)
!214 = !DILexicalBlockFile(scope: !215, file: !1, discriminator: 6)
!215 = distinct !DILexicalBlock(scope: !216, file: !1, line: 180, column: 2)
!216 = distinct !DILexicalBlock(scope: !196, file: !1, line: 180, column: 2)
!217 = !DILocation(line: 180, column: 2, scope: !218)
!218 = !DILexicalBlockFile(scope: !196, file: !1, discriminator: 7)
!219 = !DILocation(line: 182, column: 2, scope: !144)
!220 = !DILocation(line: 182, column: 8, scope: !144)
!221 = !DILocation(line: 182, column: 18, scope: !144)
!222 = !DILocation(line: 182, column: 46, scope: !144)
!223 = !DILocation(line: 183, column: 2, scope: !144)
!224 = !DILocation(line: 183, column: 8, scope: !144)
!225 = !DILocation(line: 183, column: 18, scope: !144)
!226 = !DILocation(line: 183, column: 49, scope: !144)
!227 = !DILocation(line: 185, column: 2, scope: !144)
!228 = !DILocation(line: 186, column: 1, scope: !144)
!229 = !DILocalVariable(name: "next", arg: 1, scope: !173, file: !1, line: 146, type: !176)
!230 = !DILocation(line: 146, column: 36, scope: !173)
!231 = !DILocalVariable(name: "allocator", arg: 2, scope: !173, file: !1, line: 146, type: !43)
!232 = !DILocation(line: 146, column: 58, scope: !173)
!233 = !DILocalVariable(name: "memlimit", arg: 3, scope: !173, file: !1, line: 147, type: !32)
!234 = !DILocation(line: 147, column: 12, scope: !173)
!235 = !DILocalVariable(name: "flags", arg: 4, scope: !173, file: !1, line: 147, type: !113)
!236 = !DILocation(line: 147, column: 31, scope: !173)
!237 = !DILocation(line: 149, column: 2, scope: !173)
!238 = !DILocation(line: 149, column: 2, scope: !239)
!239 = !DILexicalBlockFile(scope: !240, file: !1, discriminator: 1)
!240 = distinct !DILexicalBlock(scope: !241, file: !1, line: 149, column: 2)
!241 = distinct !DILexicalBlock(scope: !173, file: !1, line: 149, column: 2)
!242 = !DILocation(line: 149, column: 2, scope: !243)
!243 = !DILexicalBlockFile(scope: !240, file: !1, discriminator: 2)
!244 = !DILocation(line: 149, column: 2, scope: !245)
!245 = !DILexicalBlockFile(scope: !241, file: !1, discriminator: 3)
!246 = !DILocation(line: 151, column: 6, scope: !247)
!247 = distinct !DILexicalBlock(scope: !173, file: !1, line: 151, column: 6)
!248 = !DILocation(line: 151, column: 15, scope: !247)
!249 = !DILocation(line: 151, column: 6, scope: !173)
!250 = !DILocation(line: 152, column: 3, scope: !247)
!251 = !DILocation(line: 154, column: 6, scope: !252)
!252 = distinct !DILexicalBlock(scope: !173, file: !1, line: 154, column: 6)
!253 = !DILocation(line: 154, column: 12, scope: !252)
!254 = !DILocation(line: 154, column: 6, scope: !173)
!255 = !DILocation(line: 155, column: 3, scope: !252)
!256 = !DILocation(line: 157, column: 6, scope: !257)
!257 = distinct !DILexicalBlock(scope: !173, file: !1, line: 157, column: 6)
!258 = !DILocation(line: 157, column: 12, scope: !257)
!259 = !DILocation(line: 157, column: 18, scope: !257)
!260 = !DILocation(line: 157, column: 6, scope: !173)
!261 = !DILocation(line: 158, column: 48, scope: !262)
!262 = distinct !DILexicalBlock(scope: !257, file: !1, line: 157, column: 27)
!263 = !DILocation(line: 158, column: 17, scope: !262)
!264 = !DILocation(line: 158, column: 3, scope: !262)
!265 = !DILocation(line: 158, column: 9, scope: !262)
!266 = !DILocation(line: 158, column: 15, scope: !262)
!267 = !DILocation(line: 159, column: 7, scope: !268)
!268 = distinct !DILexicalBlock(scope: !262, file: !1, line: 159, column: 7)
!269 = !DILocation(line: 159, column: 13, scope: !268)
!270 = !DILocation(line: 159, column: 19, scope: !268)
!271 = !DILocation(line: 159, column: 7, scope: !262)
!272 = !DILocation(line: 160, column: 4, scope: !268)
!273 = !DILocation(line: 162, column: 3, scope: !262)
!274 = !DILocation(line: 162, column: 9, scope: !262)
!275 = !DILocation(line: 162, column: 14, scope: !262)
!276 = !DILocation(line: 163, column: 3, scope: !262)
!277 = !DILocation(line: 163, column: 9, scope: !262)
!278 = !DILocation(line: 163, column: 13, scope: !262)
!279 = !DILocation(line: 164, column: 3, scope: !262)
!280 = !DILocation(line: 164, column: 9, scope: !262)
!281 = !DILocation(line: 164, column: 19, scope: !262)
!282 = !DILocation(line: 165, column: 3, scope: !262)
!283 = !DILocation(line: 165, column: 9, scope: !262)
!284 = !DILocation(line: 165, column: 19, scope: !262)
!285 = !DILocation(line: 166, column: 3, scope: !262)
!286 = !DILocation(line: 166, column: 9, scope: !262)
!287 = !DILocation(line: 166, column: 16, scope: !262)
!288 = !DILocation(line: 166, column: 23, scope: !262)
!289 = !DILocation(line: 167, column: 2, scope: !262)
!290 = !DILocation(line: 169, column: 26, scope: !173)
!291 = !DILocation(line: 169, column: 2, scope: !173)
!292 = !DILocation(line: 169, column: 8, scope: !173)
!293 = !DILocation(line: 169, column: 15, scope: !173)
!294 = !DILocation(line: 169, column: 24, scope: !173)
!295 = !DILocation(line: 170, column: 23, scope: !173)
!296 = !DILocation(line: 170, column: 2, scope: !173)
!297 = !DILocation(line: 170, column: 8, scope: !173)
!298 = !DILocation(line: 170, column: 15, scope: !173)
!299 = !DILocation(line: 170, column: 21, scope: !173)
!300 = !DILocation(line: 171, column: 2, scope: !173)
!301 = !DILocation(line: 171, column: 8, scope: !173)
!302 = !DILocation(line: 171, column: 15, scope: !173)
!303 = !DILocation(line: 171, column: 24, scope: !173)
!304 = !DILocation(line: 173, column: 2, scope: !173)
!305 = !DILocation(line: 174, column: 1, scope: !173)
!306 = !DILocalVariable(name: "coder", arg: 1, scope: !177, file: !1, line: 33, type: !27)
!307 = !DILocation(line: 33, column: 25, scope: !177)
!308 = !DILocalVariable(name: "allocator", arg: 2, scope: !177, file: !1, line: 33, type: !43)
!309 = !DILocation(line: 33, column: 48, scope: !177)
!310 = !DILocalVariable(name: "in", arg: 3, scope: !177, file: !1, line: 34, type: !59)
!311 = !DILocation(line: 34, column: 32, scope: !177)
!312 = !DILocalVariable(name: "in_pos", arg: 4, scope: !177, file: !1, line: 34, type: !64)
!313 = !DILocation(line: 34, column: 58, scope: !177)
!314 = !DILocalVariable(name: "in_size", arg: 5, scope: !177, file: !1, line: 35, type: !52)
!315 = !DILocation(line: 35, column: 10, scope: !177)
!316 = !DILocalVariable(name: "out", arg: 6, scope: !177, file: !1, line: 35, type: !66)
!317 = !DILocation(line: 35, column: 42, scope: !177)
!318 = !DILocalVariable(name: "out_pos", arg: 7, scope: !177, file: !1, line: 36, type: !64)
!319 = !DILocation(line: 36, column: 25, scope: !177)
!320 = !DILocalVariable(name: "out_size", arg: 8, scope: !177, file: !1, line: 36, type: !52)
!321 = !DILocation(line: 36, column: 41, scope: !177)
!322 = !DILocalVariable(name: "action", arg: 9, scope: !177, file: !1, line: 36, type: !68)
!323 = !DILocation(line: 36, column: 63, scope: !177)
!324 = !DILocation(line: 38, column: 10, scope: !177)
!325 = !DILocation(line: 38, column: 17, scope: !177)
!326 = !DILocation(line: 38, column: 2, scope: !177)
!327 = !DILocation(line: 40, column: 8, scope: !328)
!328 = distinct !DILexicalBlock(scope: !329, file: !1, line: 40, column: 7)
!329 = distinct !DILexicalBlock(scope: !177, file: !1, line: 38, column: 27)
!330 = !DILocation(line: 40, column: 7, scope: !328)
!331 = !DILocation(line: 40, column: 18, scope: !328)
!332 = !DILocation(line: 40, column: 15, scope: !328)
!333 = !DILocation(line: 40, column: 7, scope: !329)
!334 = !DILocation(line: 41, column: 4, scope: !328)
!335 = !DILocation(line: 45, column: 3, scope: !329)
!336 = !DILocation(line: 45, column: 10, scope: !329)
!337 = !DILocation(line: 45, column: 19, scope: !329)
!338 = !DILocation(line: 51, column: 11, scope: !339)
!339 = distinct !DILexicalBlock(scope: !329, file: !1, line: 51, column: 7)
!340 = !DILocation(line: 51, column: 10, scope: !339)
!341 = !DILocation(line: 51, column: 7, scope: !339)
!342 = !DILocation(line: 51, column: 19, scope: !339)
!343 = !DILocation(line: 51, column: 7, scope: !329)
!344 = !DILocation(line: 52, column: 4, scope: !345)
!345 = distinct !DILexicalBlock(scope: !339, file: !1, line: 51, column: 28)
!346 = !DILocalVariable(name: "ret_", scope: !347, file: !1, line: 52, type: !202)
!347 = distinct !DILexicalBlock(scope: !345, file: !1, line: 52, column: 4)
!348 = !DILocation(line: 52, column: 4, scope: !347)
!349 = !DILocation(line: 52, column: 4, scope: !350)
!350 = !DILexicalBlockFile(scope: !347, file: !1, discriminator: 1)
!351 = !DILocation(line: 52, column: 4, scope: !352)
!352 = !DILexicalBlockFile(scope: !353, file: !1, discriminator: 2)
!353 = distinct !DILexicalBlock(scope: !347, file: !1, line: 52, column: 4)
!354 = !DILocation(line: 52, column: 4, scope: !355)
!355 = !DILexicalBlockFile(scope: !347, file: !1, discriminator: 3)
!356 = !DILocation(line: 55, column: 3, scope: !345)
!357 = !DILocation(line: 56, column: 4, scope: !358)
!358 = distinct !DILexicalBlock(scope: !339, file: !1, line: 55, column: 10)
!359 = !DILocalVariable(name: "ret_", scope: !360, file: !1, line: 56, type: !202)
!360 = distinct !DILexicalBlock(scope: !358, file: !1, line: 56, column: 4)
!361 = !DILocation(line: 56, column: 4, scope: !360)
!362 = !DILocation(line: 56, column: 4, scope: !363)
!363 = !DILexicalBlockFile(scope: !360, file: !1, discriminator: 1)
!364 = !DILocation(line: 56, column: 4, scope: !365)
!365 = !DILexicalBlockFile(scope: !366, file: !1, discriminator: 2)
!366 = distinct !DILexicalBlock(scope: !360, file: !1, line: 56, column: 4)
!367 = !DILocation(line: 56, column: 4, scope: !368)
!368 = !DILexicalBlockFile(scope: !360, file: !1, discriminator: 3)
!369 = !DILocation(line: 63, column: 8, scope: !370)
!370 = distinct !DILexicalBlock(scope: !358, file: !1, line: 63, column: 8)
!371 = !DILocation(line: 63, column: 15, scope: !370)
!372 = !DILocation(line: 63, column: 21, scope: !370)
!373 = !DILocation(line: 63, column: 8, scope: !358)
!374 = !DILocation(line: 64, column: 5, scope: !370)
!375 = !DILocation(line: 66, column: 8, scope: !376)
!376 = distinct !DILexicalBlock(scope: !358, file: !1, line: 66, column: 8)
!377 = !DILocation(line: 66, column: 15, scope: !376)
!378 = !DILocation(line: 66, column: 21, scope: !376)
!379 = !DILocation(line: 66, column: 8, scope: !358)
!380 = !DILocation(line: 67, column: 5, scope: !376)
!381 = !DILocation(line: 51, column: 22, scope: !382)
!382 = !DILexicalBlockFile(scope: !339, file: !1, discriminator: 1)
!383 = !DILocalVariable(name: "ret", scope: !384, file: !1, line: 73, type: !202)
!384 = distinct !DILexicalBlock(scope: !329, file: !1, line: 72, column: 17)
!385 = !DILocation(line: 73, column: 18, scope: !384)
!386 = !DILocation(line: 73, column: 24, scope: !384)
!387 = !DILocation(line: 73, column: 31, scope: !384)
!388 = !DILocation(line: 73, column: 36, scope: !384)
!389 = !DILocation(line: 74, column: 5, scope: !384)
!390 = !DILocation(line: 74, column: 12, scope: !384)
!391 = !DILocation(line: 74, column: 17, scope: !384)
!392 = !DILocation(line: 74, column: 24, scope: !384)
!393 = !DILocation(line: 75, column: 5, scope: !384)
!394 = !DILocation(line: 75, column: 9, scope: !384)
!395 = !DILocation(line: 75, column: 17, scope: !384)
!396 = !DILocation(line: 76, column: 5, scope: !384)
!397 = !DILocation(line: 76, column: 10, scope: !384)
!398 = !DILocation(line: 76, column: 19, scope: !384)
!399 = !DILocation(line: 76, column: 29, scope: !384)
!400 = !DILocation(line: 77, column: 7, scope: !401)
!401 = distinct !DILexicalBlock(scope: !384, file: !1, line: 77, column: 7)
!402 = !DILocation(line: 77, column: 11, scope: !401)
!403 = !DILocation(line: 78, column: 5, scope: !401)
!404 = !DILocation(line: 78, column: 9, scope: !405)
!405 = !DILexicalBlockFile(scope: !401, file: !1, discriminator: 1)
!406 = !DILocation(line: 78, column: 16, scope: !405)
!407 = !DILocation(line: 78, column: 22, scope: !405)
!408 = !DILocation(line: 78, column: 43, scope: !405)
!409 = !DILocation(line: 77, column: 7, scope: !410)
!410 = !DILexicalBlockFile(scope: !384, file: !1, discriminator: 1)
!411 = !DILocation(line: 79, column: 11, scope: !401)
!412 = !DILocation(line: 79, column: 4, scope: !401)
!413 = !DILocation(line: 81, column: 3, scope: !384)
!414 = !DILocation(line: 81, column: 10, scope: !384)
!415 = !DILocation(line: 81, column: 19, scope: !384)
!416 = !DILocation(line: 82, column: 2, scope: !384)
!417 = !DILocation(line: 90, column: 8, scope: !418)
!418 = distinct !DILexicalBlock(scope: !329, file: !1, line: 90, column: 7)
!419 = !DILocation(line: 90, column: 7, scope: !418)
!420 = !DILocation(line: 90, column: 17, scope: !418)
!421 = !DILocation(line: 90, column: 15, scope: !418)
!422 = !DILocation(line: 90, column: 7, scope: !329)
!423 = !DILocation(line: 91, column: 4, scope: !418)
!424 = !DILocation(line: 93, column: 10, scope: !329)
!425 = !DILocation(line: 93, column: 17, scope: !329)
!426 = !DILocation(line: 93, column: 3, scope: !329)
!427 = !DILocation(line: 96, column: 3, scope: !329)
!428 = !DILocation(line: 99, column: 1, scope: !177)
!429 = !DILocalVariable(name: "coder", arg: 1, scope: !178, file: !1, line: 103, type: !27)
!430 = !DILocation(line: 103, column: 30, scope: !178)
!431 = !DILocalVariable(name: "allocator", arg: 2, scope: !178, file: !1, line: 103, type: !43)
!432 = !DILocation(line: 103, column: 53, scope: !178)
!433 = !DILocation(line: 105, column: 17, scope: !178)
!434 = !DILocation(line: 105, column: 24, scope: !178)
!435 = !DILocation(line: 105, column: 30, scope: !178)
!436 = !DILocation(line: 105, column: 2, scope: !178)
!437 = !DILocation(line: 106, column: 12, scope: !178)
!438 = !DILocation(line: 106, column: 19, scope: !178)
!439 = !DILocation(line: 106, column: 2, scope: !178)
!440 = !DILocation(line: 107, column: 2, scope: !178)
!441 = !DILocalVariable(name: "coder", arg: 1, scope: !179, file: !1, line: 112, type: !92)
!442 = !DILocation(line: 112, column: 42, scope: !179)
!443 = !DILocation(line: 115, column: 9, scope: !179)
!444 = !DILocation(line: 115, column: 16, scope: !179)
!445 = !DILocation(line: 115, column: 21, scope: !179)
!446 = !DILocation(line: 115, column: 31, scope: !179)
!447 = !DILocation(line: 115, column: 9, scope: !448)
!448 = !DILexicalBlockFile(scope: !179, file: !1, discriminator: 1)
!449 = !DILocation(line: 116, column: 6, scope: !179)
!450 = !DILocation(line: 116, column: 13, scope: !179)
!451 = !DILocation(line: 116, column: 18, scope: !179)
!452 = !DILocation(line: 116, column: 28, scope: !179)
!453 = !DILocation(line: 116, column: 35, scope: !179)
!454 = !DILocation(line: 116, column: 40, scope: !179)
!455 = !DILocation(line: 115, column: 9, scope: !456)
!456 = !DILexicalBlockFile(scope: !179, file: !1, discriminator: 2)
!457 = !DILocation(line: 115, column: 9, scope: !458)
!458 = !DILexicalBlockFile(scope: !179, file: !1, discriminator: 3)
!459 = !DILocation(line: 115, column: 2, scope: !458)
!460 = !DILocalVariable(name: "coder", arg: 1, scope: !180, file: !1, line: 121, type: !27)
!461 = !DILocation(line: 121, column: 36, scope: !180)
!462 = !DILocalVariable(name: "memusage", arg: 2, scope: !180, file: !1, line: 121, type: !98)
!463 = !DILocation(line: 121, column: 53, scope: !180)
!464 = !DILocalVariable(name: "old_memlimit", arg: 3, scope: !180, file: !1, line: 122, type: !98)
!465 = !DILocation(line: 122, column: 13, scope: !180)
!466 = !DILocalVariable(name: "new_memlimit", arg: 4, scope: !180, file: !1, line: 122, type: !32)
!467 = !DILocation(line: 122, column: 36, scope: !180)
!468 = !DILocalVariable(name: "ret", scope: !180, file: !1, line: 124, type: !42)
!469 = !DILocation(line: 124, column: 11, scope: !180)
!470 = !DILocation(line: 126, column: 6, scope: !471)
!471 = distinct !DILexicalBlock(scope: !180, file: !1, line: 126, column: 6)
!472 = !DILocation(line: 126, column: 13, scope: !471)
!473 = !DILocation(line: 126, column: 18, scope: !471)
!474 = !DILocation(line: 126, column: 28, scope: !471)
!475 = !DILocation(line: 126, column: 6, scope: !180)
!476 = !DILocation(line: 127, column: 9, scope: !477)
!477 = distinct !DILexicalBlock(scope: !471, file: !1, line: 126, column: 37)
!478 = !DILocation(line: 127, column: 16, scope: !477)
!479 = !DILocation(line: 127, column: 21, scope: !477)
!480 = !DILocation(line: 127, column: 31, scope: !477)
!481 = !DILocation(line: 127, column: 38, scope: !477)
!482 = !DILocation(line: 127, column: 43, scope: !477)
!483 = !DILocation(line: 128, column: 5, scope: !477)
!484 = !DILocation(line: 128, column: 15, scope: !477)
!485 = !DILocation(line: 128, column: 29, scope: !477)
!486 = !DILocation(line: 127, column: 7, scope: !477)
!487 = !DILocation(line: 129, column: 3, scope: !477)
!488 = !DILocation(line: 129, column: 3, scope: !489)
!489 = !DILexicalBlockFile(scope: !477, file: !1, discriminator: 1)
!490 = !DILocation(line: 129, column: 3, scope: !491)
!491 = !DILexicalBlockFile(scope: !477, file: !1, discriminator: 2)
!492 = !DILocation(line: 129, column: 3, scope: !493)
!493 = !DILexicalBlockFile(scope: !477, file: !1, discriminator: 3)
!494 = !DILocation(line: 130, column: 2, scope: !477)
!495 = !DILocation(line: 133, column: 4, scope: !496)
!496 = distinct !DILexicalBlock(scope: !471, file: !1, line: 130, column: 9)
!497 = !DILocation(line: 133, column: 13, scope: !496)
!498 = !DILocation(line: 134, column: 19, scope: !496)
!499 = !DILocation(line: 134, column: 26, scope: !496)
!500 = !DILocation(line: 134, column: 4, scope: !496)
!501 = !DILocation(line: 134, column: 17, scope: !496)
!502 = !DILocation(line: 135, column: 7, scope: !496)
!503 = !DILocation(line: 138, column: 6, scope: !504)
!504 = distinct !DILexicalBlock(scope: !180, file: !1, line: 138, column: 6)
!505 = !DILocation(line: 138, column: 10, scope: !504)
!506 = !DILocation(line: 138, column: 21, scope: !504)
!507 = !DILocation(line: 138, column: 24, scope: !508)
!508 = !DILexicalBlockFile(scope: !504, file: !1, discriminator: 1)
!509 = !DILocation(line: 138, column: 37, scope: !508)
!510 = !DILocation(line: 138, column: 6, scope: !508)
!511 = !DILocation(line: 139, column: 21, scope: !504)
!512 = !DILocation(line: 139, column: 3, scope: !504)
!513 = !DILocation(line: 139, column: 10, scope: !504)
!514 = !DILocation(line: 139, column: 19, scope: !504)
!515 = !DILocation(line: 141, column: 9, scope: !180)
!516 = !DILocation(line: 141, column: 2, scope: !180)
