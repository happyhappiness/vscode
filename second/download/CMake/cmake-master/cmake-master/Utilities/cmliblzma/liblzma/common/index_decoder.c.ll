; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/index_decoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_stream = type { i8*, i64, i64, i8*, i64, i64, %struct.lzma_allocator*, %struct.lzma_internal_s*, i8*, i8*, i8*, i8*, i64, i64, i64, i64, i32, i32 }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_internal_s = type { %struct.lzma_next_coder_s, i32, i64, [4 x i8], i8 }
%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type { i32, i64, %struct.lzma_index_s*, %struct.lzma_index_s**, i64, i64, i64, i64, i32 }
%struct.lzma_index_s = type opaque
%struct.lzma_filter = type { i64, i8* }

@.str = private unnamed_addr constant [2 x i8] c"0\00", align 1
@.str.1 = private unnamed_addr constant [85 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/index_decoder.c\00", align 1
@__PRETTY_FUNCTION__.index_decode = private unnamed_addr constant [163 x i8] c"lzma_ret index_decode(lzma_coder *, lzma_allocator *, const uint8_t *restrict, size_t *restrict, size_t, uint8_t *restrict, size_t *restrict, size_t, lzma_action)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @lzma_index_decoder(%struct.lzma_stream* %strm, %struct.lzma_index_s** %i, i64 %memlimit) #0 !dbg !159 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.lzma_stream*, align 8
  %i.addr = alloca %struct.lzma_index_s**, align 8
  %memlimit.addr = alloca i64, align 8
  %ret_ = alloca i32, align 4
  %ret_2 = alloca i32, align 4
  store %struct.lzma_stream* %strm, %struct.lzma_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream** %strm.addr, metadata !204, metadata !205), !dbg !206
  store %struct.lzma_index_s** %i, %struct.lzma_index_s*** %i.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s*** %i.addr, metadata !207, metadata !205), !dbg !208
  store i64 %memlimit, i64* %memlimit.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %memlimit.addr, metadata !209, metadata !205), !dbg !210
  br label %do.body, !dbg !211

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !212, metadata !205), !dbg !214
  br label %do.body1, !dbg !215

do.body1:                                         ; preds = %do.body
  call void @llvm.dbg.declare(metadata i32* %ret_2, metadata !217, metadata !205), !dbg !220
  %0 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !221
  %call = call i32 @lzma_strm_init(%struct.lzma_stream* %0), !dbg !221
  store i32 %call, i32* %ret_2, align 4, !dbg !221
  %1 = load i32, i32* %ret_2, align 4, !dbg !221
  %cmp = icmp ne i32 %1, 0, !dbg !221
  br i1 %cmp, label %if.then, label %if.end, !dbg !221

if.then:                                          ; preds = %do.body1
  %2 = load i32, i32* %ret_2, align 4, !dbg !223
  store i32 %2, i32* %retval, align 4, !dbg !223
  br label %return, !dbg !223

if.end:                                           ; preds = %do.body1
  br label %do.end, !dbg !226

do.end:                                           ; preds = %if.end
  %3 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !228
  %internal = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %3, i32 0, i32 7, !dbg !228
  %4 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal, align 8, !dbg !228
  %next = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %4, i32 0, i32 0, !dbg !228
  %5 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !228
  %allocator = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %5, i32 0, i32 6, !dbg !228
  %6 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator, align 8, !dbg !228
  %7 = load %struct.lzma_index_s**, %struct.lzma_index_s*** %i.addr, align 8, !dbg !228
  %8 = load i64, i64* %memlimit.addr, align 8, !dbg !228
  %call3 = call i32 @index_decoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %6, %struct.lzma_index_s** %7, i64 %8), !dbg !228
  store i32 %call3, i32* %ret_, align 4, !dbg !228
  %9 = load i32, i32* %ret_, align 4, !dbg !228
  %cmp4 = icmp ne i32 %9, 0, !dbg !228
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !228

if.then5:                                         ; preds = %do.end
  %10 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !230
  call void @lzma_end(%struct.lzma_stream* %10) #6, !dbg !230
  %11 = load i32, i32* %ret_, align 4, !dbg !230
  store i32 %11, i32* %retval, align 4, !dbg !230
  br label %return, !dbg !230

if.end6:                                          ; preds = %do.end
  br label %do.end7, !dbg !234

do.end7:                                          ; preds = %if.end6
  %12 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !236
  %internal8 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %12, i32 0, i32 7, !dbg !237
  %13 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal8, align 8, !dbg !237
  %supported_actions = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %13, i32 0, i32 3, !dbg !238
  %arrayidx = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions, i64 0, i64 0, !dbg !236
  store i8 1, i8* %arrayidx, align 8, !dbg !239
  %14 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !240
  %internal9 = getelementptr inbounds %struct.lzma_stream, %struct.lzma_stream* %14, i32 0, i32 7, !dbg !241
  %15 = load %struct.lzma_internal_s*, %struct.lzma_internal_s** %internal9, align 8, !dbg !241
  %supported_actions10 = getelementptr inbounds %struct.lzma_internal_s, %struct.lzma_internal_s* %15, i32 0, i32 3, !dbg !242
  %arrayidx11 = getelementptr inbounds [4 x i8], [4 x i8]* %supported_actions10, i64 0, i64 3, !dbg !240
  store i8 1, i8* %arrayidx11, align 1, !dbg !243
  store i32 0, i32* %retval, align 4, !dbg !244
  br label %return, !dbg !244

return:                                           ; preds = %do.end7, %if.then5, %if.then
  %16 = load i32, i32* %retval, align 4, !dbg !245
  ret i32 %16, !dbg !245
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @lzma_strm_init(%struct.lzma_stream*) #2

; Function Attrs: nounwind uwtable
define internal i32 @index_decoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %allocator, %struct.lzma_index_s** %i, i64 %memlimit) #0 !dbg !191 {
entry:
  %retval = alloca i32, align 4
  %next.addr = alloca %struct.lzma_next_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %i.addr = alloca %struct.lzma_index_s**, align 8
  %memlimit.addr = alloca i64, align 8
  store %struct.lzma_next_coder_s* %next, %struct.lzma_next_coder_s** %next.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s** %next.addr, metadata !246, metadata !205), !dbg !247
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !248, metadata !205), !dbg !249
  store %struct.lzma_index_s** %i, %struct.lzma_index_s*** %i.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s*** %i.addr, metadata !250, metadata !205), !dbg !251
  store i64 %memlimit, i64* %memlimit.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %memlimit.addr, metadata !252, metadata !205), !dbg !253
  br label %do.body, !dbg !254

do.body:                                          ; preds = %entry
  %0 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !255
  %init = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %0, i32 0, i32 2, !dbg !255
  %1 = load i64, i64* %init, align 8, !dbg !255
  %cmp = icmp ne i64 ptrtoint (i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_index_s**, i64)* @index_decoder_init to i64), %1, !dbg !255
  br i1 %cmp, label %if.then, label %if.end, !dbg !255

if.then:                                          ; preds = %do.body
  %2 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !259
  %3 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !259
  call void @lzma_next_end(%struct.lzma_next_coder_s* %2, %struct.lzma_allocator* %3), !dbg !259
  br label %if.end, !dbg !259

if.end:                                           ; preds = %if.then, %do.body
  %4 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !261
  %init1 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %4, i32 0, i32 2, !dbg !261
  store i64 ptrtoint (i32 (%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_index_s**, i64)* @index_decoder_init to i64), i64* %init1, align 8, !dbg !261
  br label %do.end, !dbg !261

do.end:                                           ; preds = %if.end
  %5 = load %struct.lzma_index_s**, %struct.lzma_index_s*** %i.addr, align 8, !dbg !263
  %cmp2 = icmp eq %struct.lzma_index_s** %5, null, !dbg !265
  br i1 %cmp2, label %if.then4, label %lor.lhs.false, !dbg !266

lor.lhs.false:                                    ; preds = %do.end
  %6 = load i64, i64* %memlimit.addr, align 8, !dbg !267
  %cmp3 = icmp eq i64 %6, 0, !dbg !269
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !270

if.then4:                                         ; preds = %lor.lhs.false, %do.end
  store i32 11, i32* %retval, align 4, !dbg !271
  br label %return, !dbg !271

if.end5:                                          ; preds = %lor.lhs.false
  %7 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !272
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %7, i32 0, i32 0, !dbg !274
  %8 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !274
  %cmp6 = icmp eq %struct.lzma_coder_s* %8, null, !dbg !275
  br i1 %cmp6, label %if.then7, label %if.else, !dbg !276

if.then7:                                         ; preds = %if.end5
  %9 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !277
  %call = call noalias i8* @lzma_alloc(i64 72, %struct.lzma_allocator* %9), !dbg !279
  %10 = bitcast i8* %call to %struct.lzma_coder_s*, !dbg !279
  %11 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !280
  %coder8 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %11, i32 0, i32 0, !dbg !281
  store %struct.lzma_coder_s* %10, %struct.lzma_coder_s** %coder8, align 8, !dbg !282
  %12 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !283
  %coder9 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %12, i32 0, i32 0, !dbg !285
  %13 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder9, align 8, !dbg !285
  %cmp10 = icmp eq %struct.lzma_coder_s* %13, null, !dbg !286
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !287

if.then11:                                        ; preds = %if.then7
  store i32 5, i32* %retval, align 4, !dbg !288
  br label %return, !dbg !288

if.end12:                                         ; preds = %if.then7
  %14 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !289
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %14, i32 0, i32 3, !dbg !290
  store i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* @index_decode, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !291
  %15 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !292
  %end = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %15, i32 0, i32 4, !dbg !293
  store void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* @index_decoder_end, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)** %end, align 8, !dbg !294
  %16 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !295
  %memconfig = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %16, i32 0, i32 6, !dbg !296
  store i32 (%struct.lzma_coder_s*, i64*, i64*, i64)* @index_decoder_memconfig, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)** %memconfig, align 8, !dbg !297
  %17 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !298
  %coder13 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %17, i32 0, i32 0, !dbg !299
  %18 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder13, align 8, !dbg !299
  %index = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %18, i32 0, i32 2, !dbg !300
  store %struct.lzma_index_s* null, %struct.lzma_index_s** %index, align 8, !dbg !301
  br label %if.end16, !dbg !302

if.else:                                          ; preds = %if.end5
  %19 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !303
  %coder14 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %19, i32 0, i32 0, !dbg !305
  %20 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder14, align 8, !dbg !305
  %index15 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %20, i32 0, i32 2, !dbg !306
  %21 = load %struct.lzma_index_s*, %struct.lzma_index_s** %index15, align 8, !dbg !306
  %22 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !307
  call void @lzma_index_end(%struct.lzma_index_s* %21, %struct.lzma_allocator* %22) #6, !dbg !308
  br label %if.end16

if.end16:                                         ; preds = %if.else, %if.end12
  %23 = load %struct.lzma_next_coder_s*, %struct.lzma_next_coder_s** %next.addr, align 8, !dbg !309
  %coder17 = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %23, i32 0, i32 0, !dbg !310
  %24 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder17, align 8, !dbg !310
  %25 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !311
  %26 = load %struct.lzma_index_s**, %struct.lzma_index_s*** %i.addr, align 8, !dbg !312
  %27 = load i64, i64* %memlimit.addr, align 8, !dbg !313
  %call18 = call i32 @index_decoder_reset(%struct.lzma_coder_s* %24, %struct.lzma_allocator* %25, %struct.lzma_index_s** %26, i64 %27), !dbg !314
  store i32 %call18, i32* %retval, align 4, !dbg !315
  br label %return, !dbg !315

return:                                           ; preds = %if.end16, %if.then11, %if.then4
  %28 = load i32, i32* %retval, align 4, !dbg !316
  ret i32 %28, !dbg !316
}

; Function Attrs: nounwind
declare void @lzma_end(%struct.lzma_stream*) #3

; Function Attrs: nounwind uwtable
define i32 @lzma_index_buffer_decode(%struct.lzma_index_s** %i, i64* %memlimit, %struct.lzma_allocator* %allocator, i8* %in, i64* %in_pos, i64 %in_size) #0 !dbg !188 {
entry:
  %retval = alloca i32, align 4
  %i.addr = alloca %struct.lzma_index_s**, align 8
  %memlimit.addr = alloca i64*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %in.addr = alloca i8*, align 8
  %in_pos.addr = alloca i64*, align 8
  %in_size.addr = alloca i64, align 8
  %coder = alloca %struct.lzma_coder_s, align 8
  %ret = alloca i32, align 4
  %in_start = alloca i64, align 8
  %ret_ = alloca i32, align 4
  store %struct.lzma_index_s** %i, %struct.lzma_index_s*** %i.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s*** %i.addr, metadata !317, metadata !205), !dbg !318
  store i64* %memlimit, i64** %memlimit.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %memlimit.addr, metadata !319, metadata !205), !dbg !320
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !321, metadata !205), !dbg !322
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !323, metadata !205), !dbg !324
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !325, metadata !205), !dbg !326
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !327, metadata !205), !dbg !328
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s* %coder, metadata !329, metadata !205), !dbg !330
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !331, metadata !205), !dbg !332
  call void @llvm.dbg.declare(metadata i64* %in_start, metadata !333, metadata !205), !dbg !335
  %0 = load i64*, i64** %in_pos.addr, align 8, !dbg !336
  %1 = load i64, i64* %0, align 8, !dbg !337
  store i64 %1, i64* %in_start, align 8, !dbg !335
  %2 = load %struct.lzma_index_s**, %struct.lzma_index_s*** %i.addr, align 8, !dbg !338
  %cmp = icmp eq %struct.lzma_index_s** %2, null, !dbg !340
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !341

lor.lhs.false:                                    ; preds = %entry
  %3 = load i64*, i64** %memlimit.addr, align 8, !dbg !342
  %cmp1 = icmp eq i64* %3, null, !dbg !344
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !345

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %4 = load i8*, i8** %in.addr, align 8, !dbg !346
  %cmp3 = icmp eq i8* %4, null, !dbg !347
  br i1 %cmp3, label %if.then, label %lor.lhs.false4, !dbg !348

lor.lhs.false4:                                   ; preds = %lor.lhs.false2
  %5 = load i64*, i64** %in_pos.addr, align 8, !dbg !349
  %cmp5 = icmp eq i64* %5, null, !dbg !351
  br i1 %cmp5, label %if.then, label %lor.lhs.false6, !dbg !352

lor.lhs.false6:                                   ; preds = %lor.lhs.false4
  %6 = load i64*, i64** %in_pos.addr, align 8, !dbg !353
  %7 = load i64, i64* %6, align 8, !dbg !355
  %8 = load i64, i64* %in_size.addr, align 8, !dbg !356
  %cmp7 = icmp ugt i64 %7, %8, !dbg !357
  br i1 %cmp7, label %if.then, label %if.end, !dbg !358

if.then:                                          ; preds = %lor.lhs.false6, %lor.lhs.false4, %lor.lhs.false2, %lor.lhs.false, %entry
  store i32 11, i32* %retval, align 4, !dbg !360
  br label %return, !dbg !360

if.end:                                           ; preds = %lor.lhs.false6
  br label %do.body, !dbg !361

do.body:                                          ; preds = %if.end
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !362, metadata !205), !dbg !364
  %9 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !365
  %10 = load %struct.lzma_index_s**, %struct.lzma_index_s*** %i.addr, align 8, !dbg !365
  %11 = load i64*, i64** %memlimit.addr, align 8, !dbg !365
  %12 = load i64, i64* %11, align 8, !dbg !365
  %call = call i32 @index_decoder_reset(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %9, %struct.lzma_index_s** %10, i64 %12), !dbg !365
  store i32 %call, i32* %ret_, align 4, !dbg !365
  %13 = load i32, i32* %ret_, align 4, !dbg !365
  %cmp8 = icmp ne i32 %13, 0, !dbg !365
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !365

if.then9:                                         ; preds = %do.body
  %14 = load i32, i32* %ret_, align 4, !dbg !367
  store i32 %14, i32* %retval, align 4, !dbg !367
  br label %return, !dbg !367

if.end10:                                         ; preds = %do.body
  br label %do.end, !dbg !370

do.end:                                           ; preds = %if.end10
  %15 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !372
  %16 = load i8*, i8** %in.addr, align 8, !dbg !373
  %17 = load i64*, i64** %in_pos.addr, align 8, !dbg !374
  %18 = load i64, i64* %in_size.addr, align 8, !dbg !375
  %call11 = call i32 @index_decode(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %15, i8* %16, i64* %17, i64 %18, i8* null, i64* null, i64 0, i32 0), !dbg !376
  store i32 %call11, i32* %ret, align 4, !dbg !377
  %19 = load i32, i32* %ret, align 4, !dbg !378
  %cmp12 = icmp eq i32 %19, 1, !dbg !380
  br i1 %cmp12, label %if.then13, label %if.else, !dbg !381

if.then13:                                        ; preds = %do.end
  store i32 0, i32* %ret, align 4, !dbg !382
  br label %if.end22, !dbg !384

if.else:                                          ; preds = %do.end
  %index = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %coder, i32 0, i32 2, !dbg !385
  %20 = load %struct.lzma_index_s*, %struct.lzma_index_s** %index, align 8, !dbg !385
  %21 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !387
  call void @lzma_index_end(%struct.lzma_index_s* %20, %struct.lzma_allocator* %21) #6, !dbg !388
  %22 = load i64, i64* %in_start, align 8, !dbg !389
  %23 = load i64*, i64** %in_pos.addr, align 8, !dbg !390
  store i64 %22, i64* %23, align 8, !dbg !391
  %24 = load i32, i32* %ret, align 4, !dbg !392
  %cmp14 = icmp eq i32 %24, 0, !dbg !394
  br i1 %cmp14, label %if.then15, label %if.else16, !dbg !395

if.then15:                                        ; preds = %if.else
  store i32 9, i32* %ret, align 4, !dbg !396
  br label %if.end21, !dbg !398

if.else16:                                        ; preds = %if.else
  %25 = load i32, i32* %ret, align 4, !dbg !399
  %cmp17 = icmp eq i32 %25, 6, !dbg !402
  br i1 %cmp17, label %if.then18, label %if.end20, !dbg !399

if.then18:                                        ; preds = %if.else16
  %count = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %coder, i32 0, i32 4, !dbg !403
  %26 = load i64, i64* %count, align 8, !dbg !403
  %call19 = call i64 @lzma_index_memusage(i64 1, i64 %26) #6, !dbg !405
  %27 = load i64*, i64** %memlimit.addr, align 8, !dbg !406
  store i64 %call19, i64* %27, align 8, !dbg !407
  br label %if.end20, !dbg !408

if.end20:                                         ; preds = %if.then18, %if.else16
  br label %if.end21

if.end21:                                         ; preds = %if.end20, %if.then15
  br label %if.end22

if.end22:                                         ; preds = %if.end21, %if.then13
  %28 = load i32, i32* %ret, align 4, !dbg !409
  store i32 %28, i32* %retval, align 4, !dbg !410
  br label %return, !dbg !410

return:                                           ; preds = %if.end22, %if.then9, %if.then
  %29 = load i32, i32* %retval, align 4, !dbg !411
  ret i32 %29, !dbg !411
}

; Function Attrs: nounwind uwtable
define internal i32 @index_decoder_reset(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator, %struct.lzma_index_s** %i, i64 %memlimit) #0 !dbg !197 {
entry:
  %retval = alloca i32, align 4
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %i.addr = alloca %struct.lzma_index_s**, align 8
  %memlimit.addr = alloca i64, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !412, metadata !205), !dbg !413
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !414, metadata !205), !dbg !415
  store %struct.lzma_index_s** %i, %struct.lzma_index_s*** %i.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s*** %i.addr, metadata !416, metadata !205), !dbg !417
  store i64 %memlimit, i64* %memlimit.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %memlimit.addr, metadata !418, metadata !205), !dbg !419
  %0 = load %struct.lzma_index_s**, %struct.lzma_index_s*** %i.addr, align 8, !dbg !420
  %1 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !421
  %index_ptr = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %1, i32 0, i32 3, !dbg !422
  store %struct.lzma_index_s** %0, %struct.lzma_index_s*** %index_ptr, align 8, !dbg !423
  %2 = load %struct.lzma_index_s**, %struct.lzma_index_s*** %i.addr, align 8, !dbg !424
  store %struct.lzma_index_s* null, %struct.lzma_index_s** %2, align 8, !dbg !425
  %3 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !426
  %call = call %struct.lzma_index_s* @lzma_index_init(%struct.lzma_allocator* %3) #6, !dbg !427
  %4 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !428
  %index = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %4, i32 0, i32 2, !dbg !429
  store %struct.lzma_index_s* %call, %struct.lzma_index_s** %index, align 8, !dbg !430
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !431
  %index1 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 2, !dbg !433
  %6 = load %struct.lzma_index_s*, %struct.lzma_index_s** %index1, align 8, !dbg !433
  %cmp = icmp eq %struct.lzma_index_s* %6, null, !dbg !434
  br i1 %cmp, label %if.then, label %if.end, !dbg !435

if.then:                                          ; preds = %entry
  store i32 5, i32* %retval, align 4, !dbg !436
  br label %return, !dbg !436

if.end:                                           ; preds = %entry
  %7 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !437
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %7, i32 0, i32 0, !dbg !438
  store i32 0, i32* %sequence, align 8, !dbg !439
  %8 = load i64, i64* %memlimit.addr, align 8, !dbg !440
  %9 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !441
  %memlimit2 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %9, i32 0, i32 1, !dbg !442
  store i64 %8, i64* %memlimit2, align 8, !dbg !443
  %10 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !444
  %count = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %10, i32 0, i32 4, !dbg !445
  store i64 0, i64* %count, align 8, !dbg !446
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !447
  %pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 7, !dbg !448
  store i64 0, i64* %pos, align 8, !dbg !449
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !450
  %crc32 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %12, i32 0, i32 8, !dbg !451
  store i32 0, i32* %crc32, align 8, !dbg !452
  store i32 0, i32* %retval, align 4, !dbg !453
  br label %return, !dbg !453

return:                                           ; preds = %if.end, %if.then
  %13 = load i32, i32* %retval, align 4, !dbg !454
  ret i32 %13, !dbg !454
}

; Function Attrs: nounwind uwtable
define internal i32 @index_decode(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator, i8* noalias %in, i64* noalias %in_pos, i64 %in_size, i8* noalias %out, i64* noalias %out_pos, i64 %out_size, i32 %action) #0 !dbg !200 {
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
  %in_start = alloca i64, align 8
  %ret = alloca i32, align 4
  %size = alloca i64*, align 8
  %ret_ = alloca i32, align 4
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !455, metadata !205), !dbg !456
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !457, metadata !205), !dbg !458
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !459, metadata !205), !dbg !460
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !461, metadata !205), !dbg !462
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !463, metadata !205), !dbg !464
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !465, metadata !205), !dbg !466
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !467, metadata !205), !dbg !468
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !469, metadata !205), !dbg !470
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !471, metadata !205), !dbg !472
  call void @llvm.dbg.declare(metadata i64* %in_start, metadata !473, metadata !205), !dbg !474
  %0 = load i64*, i64** %in_pos.addr, align 8, !dbg !475
  %1 = load i64, i64* %0, align 8, !dbg !476
  store i64 %1, i64* %in_start, align 8, !dbg !474
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !477, metadata !205), !dbg !478
  store i32 0, i32* %ret, align 4, !dbg !478
  br label %while.cond, !dbg !479

while.cond:                                       ; preds = %sw.epilog, %entry
  %2 = load i64*, i64** %in_pos.addr, align 8, !dbg !480
  %3 = load i64, i64* %2, align 8, !dbg !482
  %4 = load i64, i64* %in_size.addr, align 8, !dbg !483
  %cmp = icmp ult i64 %3, %4, !dbg !484
  br i1 %cmp, label %while.body, label %while.end, !dbg !485

while.body:                                       ; preds = %while.cond
  %5 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !486
  %sequence = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %5, i32 0, i32 0, !dbg !487
  %6 = load i32, i32* %sequence, align 8, !dbg !487
  switch i32 %6, label %sw.default [
    i32 0, label %sw.bb
    i32 1, label %sw.bb4
    i32 2, label %sw.bb11
    i32 3, label %sw.bb23
    i32 4, label %sw.bb23
    i32 5, label %sw.bb62
    i32 6, label %sw.bb68
    i32 7, label %sw.bb86
  ], !dbg !488

sw.bb:                                            ; preds = %while.body
  %7 = load i64*, i64** %in_pos.addr, align 8, !dbg !489
  %8 = load i64, i64* %7, align 8, !dbg !492
  %inc = add i64 %8, 1, !dbg !492
  store i64 %inc, i64* %7, align 8, !dbg !492
  %9 = load i8*, i8** %in.addr, align 8, !dbg !493
  %arrayidx = getelementptr inbounds i8, i8* %9, i64 %8, !dbg !493
  %10 = load i8, i8* %arrayidx, align 1, !dbg !493
  %conv = zext i8 %10 to i32, !dbg !493
  %cmp1 = icmp ne i32 %conv, 0, !dbg !494
  br i1 %cmp1, label %if.then, label %if.end, !dbg !495

if.then:                                          ; preds = %sw.bb
  store i32 9, i32* %retval, align 4, !dbg !496
  br label %return, !dbg !496

if.end:                                           ; preds = %sw.bb
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !497
  %sequence3 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 0, !dbg !498
  store i32 1, i32* %sequence3, align 8, !dbg !499
  br label %sw.epilog, !dbg !500

sw.bb4:                                           ; preds = %while.body
  %12 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !501
  %count = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %12, i32 0, i32 4, !dbg !502
  %13 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !503
  %pos = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %13, i32 0, i32 7, !dbg !504
  %14 = load i8*, i8** %in.addr, align 8, !dbg !505
  %15 = load i64*, i64** %in_pos.addr, align 8, !dbg !506
  %16 = load i64, i64* %in_size.addr, align 8, !dbg !507
  %call = call i32 @lzma_vli_decode(i64* %count, i64* %pos, i8* %14, i64* %15, i64 %16) #6, !dbg !508
  store i32 %call, i32* %ret, align 4, !dbg !509
  %17 = load i32, i32* %ret, align 4, !dbg !510
  %cmp5 = icmp ne i32 %17, 1, !dbg !512
  br i1 %cmp5, label %if.then7, label %if.end8, !dbg !513

if.then7:                                         ; preds = %sw.bb4
  br label %out108, !dbg !514

if.end8:                                          ; preds = %sw.bb4
  %18 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !515
  %pos9 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %18, i32 0, i32 7, !dbg !516
  store i64 0, i64* %pos9, align 8, !dbg !517
  %19 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !518
  %sequence10 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %19, i32 0, i32 0, !dbg !519
  store i32 2, i32* %sequence10, align 8, !dbg !520
  br label %sw.bb11, !dbg !518

sw.bb11:                                          ; preds = %while.body, %if.end8
  %20 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !521
  %count12 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %20, i32 0, i32 4, !dbg !523
  %21 = load i64, i64* %count12, align 8, !dbg !523
  %call13 = call i64 @lzma_index_memusage(i64 1, i64 %21) #6, !dbg !524
  %22 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !525
  %memlimit = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %22, i32 0, i32 1, !dbg !526
  %23 = load i64, i64* %memlimit, align 8, !dbg !526
  %cmp14 = icmp ugt i64 %call13, %23, !dbg !527
  br i1 %cmp14, label %if.then16, label %if.end17, !dbg !528

if.then16:                                        ; preds = %sw.bb11
  store i32 6, i32* %ret, align 4, !dbg !529
  br label %out108, !dbg !531

if.end17:                                         ; preds = %sw.bb11
  %24 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !532
  %index = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %24, i32 0, i32 2, !dbg !533
  %25 = load %struct.lzma_index_s*, %struct.lzma_index_s** %index, align 8, !dbg !533
  %26 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !534
  %count18 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %26, i32 0, i32 4, !dbg !535
  %27 = load i64, i64* %count18, align 8, !dbg !535
  call void @lzma_index_prealloc(%struct.lzma_index_s* %25, i64 %27), !dbg !536
  store i32 0, i32* %ret, align 4, !dbg !537
  %28 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !538
  %count19 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %28, i32 0, i32 4, !dbg !539
  %29 = load i64, i64* %count19, align 8, !dbg !539
  %cmp20 = icmp eq i64 %29, 0, !dbg !540
  %cond = select i1 %cmp20, i32 5, i32 3, !dbg !538
  %30 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !541
  %sequence22 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %30, i32 0, i32 0, !dbg !542
  store i32 %cond, i32* %sequence22, align 8, !dbg !543
  br label %sw.epilog, !dbg !544

sw.bb23:                                          ; preds = %while.body, %while.body
  call void @llvm.dbg.declare(metadata i64** %size, metadata !545, metadata !205), !dbg !548
  %31 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !549
  %sequence24 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %31, i32 0, i32 0, !dbg !550
  %32 = load i32, i32* %sequence24, align 8, !dbg !550
  %cmp25 = icmp eq i32 %32, 3, !dbg !551
  br i1 %cmp25, label %cond.true, label %cond.false, !dbg !549

cond.true:                                        ; preds = %sw.bb23
  %33 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !552
  %unpadded_size = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %33, i32 0, i32 5, !dbg !553
  br label %cond.end, !dbg !554

cond.false:                                       ; preds = %sw.bb23
  %34 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !556
  %uncompressed_size = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %34, i32 0, i32 6, !dbg !557
  br label %cond.end, !dbg !558

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond27 = phi i64* [ %unpadded_size, %cond.true ], [ %uncompressed_size, %cond.false ], !dbg !560
  store i64* %cond27, i64** %size, align 8, !dbg !562
  %35 = load i64*, i64** %size, align 8, !dbg !563
  %36 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !564
  %pos28 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %36, i32 0, i32 7, !dbg !565
  %37 = load i8*, i8** %in.addr, align 8, !dbg !566
  %38 = load i64*, i64** %in_pos.addr, align 8, !dbg !567
  %39 = load i64, i64* %in_size.addr, align 8, !dbg !568
  %call29 = call i32 @lzma_vli_decode(i64* %35, i64* %pos28, i8* %37, i64* %38, i64 %39) #6, !dbg !569
  store i32 %call29, i32* %ret, align 4, !dbg !570
  %40 = load i32, i32* %ret, align 4, !dbg !571
  %cmp30 = icmp ne i32 %40, 1, !dbg !573
  br i1 %cmp30, label %if.then32, label %if.end33, !dbg !574

if.then32:                                        ; preds = %cond.end
  br label %out108, !dbg !575

if.end33:                                         ; preds = %cond.end
  store i32 0, i32* %ret, align 4, !dbg !576
  %41 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !577
  %pos34 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %41, i32 0, i32 7, !dbg !578
  store i64 0, i64* %pos34, align 8, !dbg !579
  %42 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !580
  %sequence35 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %42, i32 0, i32 0, !dbg !582
  %43 = load i32, i32* %sequence35, align 8, !dbg !582
  %cmp36 = icmp eq i32 %43, 3, !dbg !583
  br i1 %cmp36, label %if.then38, label %if.else, !dbg !584

if.then38:                                        ; preds = %if.end33
  %44 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !585
  %unpadded_size39 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %44, i32 0, i32 5, !dbg !588
  %45 = load i64, i64* %unpadded_size39, align 8, !dbg !588
  %cmp40 = icmp ult i64 %45, 5, !dbg !589
  br i1 %cmp40, label %if.then45, label %lor.lhs.false, !dbg !590

lor.lhs.false:                                    ; preds = %if.then38
  %46 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !591
  %unpadded_size42 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %46, i32 0, i32 5, !dbg !593
  %47 = load i64, i64* %unpadded_size42, align 8, !dbg !593
  %cmp43 = icmp ugt i64 %47, 9223372036854775804, !dbg !594
  br i1 %cmp43, label %if.then45, label %if.end46, !dbg !595

if.then45:                                        ; preds = %lor.lhs.false, %if.then38
  store i32 9, i32* %retval, align 4, !dbg !597
  br label %return, !dbg !597

if.end46:                                         ; preds = %lor.lhs.false
  %48 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !598
  %sequence47 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %48, i32 0, i32 0, !dbg !599
  store i32 4, i32* %sequence47, align 8, !dbg !600
  br label %if.end61, !dbg !601

if.else:                                          ; preds = %if.end33
  br label %do.body, !dbg !602

do.body:                                          ; preds = %if.else
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !604, metadata !205), !dbg !606
  %49 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !607
  %index48 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %49, i32 0, i32 2, !dbg !607
  %50 = load %struct.lzma_index_s*, %struct.lzma_index_s** %index48, align 8, !dbg !607
  %51 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !607
  %52 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !607
  %unpadded_size49 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %52, i32 0, i32 5, !dbg !607
  %53 = load i64, i64* %unpadded_size49, align 8, !dbg !607
  %54 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !607
  %uncompressed_size50 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %54, i32 0, i32 6, !dbg !607
  %55 = load i64, i64* %uncompressed_size50, align 8, !dbg !607
  %call51 = call i32 @lzma_index_append(%struct.lzma_index_s* %50, %struct.lzma_allocator* %51, i64 %53, i64 %55) #6, !dbg !607
  store i32 %call51, i32* %ret_, align 4, !dbg !607
  %56 = load i32, i32* %ret_, align 4, !dbg !607
  %cmp52 = icmp ne i32 %56, 0, !dbg !607
  br i1 %cmp52, label %if.then54, label %if.end55, !dbg !607

if.then54:                                        ; preds = %do.body
  %57 = load i32, i32* %ret_, align 4, !dbg !609
  store i32 %57, i32* %retval, align 4, !dbg !609
  br label %return, !dbg !609

if.end55:                                         ; preds = %do.body
  br label %do.end, !dbg !612

do.end:                                           ; preds = %if.end55
  %58 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !614
  %count56 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %58, i32 0, i32 4, !dbg !615
  %59 = load i64, i64* %count56, align 8, !dbg !616
  %dec = add i64 %59, -1, !dbg !616
  store i64 %dec, i64* %count56, align 8, !dbg !616
  %cmp57 = icmp eq i64 %dec, 0, !dbg !617
  %cond59 = select i1 %cmp57, i32 5, i32 3, !dbg !616
  %60 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !618
  %sequence60 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %60, i32 0, i32 0, !dbg !619
  store i32 %cond59, i32* %sequence60, align 8, !dbg !620
  br label %if.end61

if.end61:                                         ; preds = %do.end, %if.end46
  br label %sw.epilog, !dbg !621

sw.bb62:                                          ; preds = %while.body
  %61 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !622
  %index63 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %61, i32 0, i32 2, !dbg !623
  %62 = load %struct.lzma_index_s*, %struct.lzma_index_s** %index63, align 8, !dbg !623
  %call64 = call i32 @lzma_index_padding_size(%struct.lzma_index_s* %62), !dbg !624
  %conv65 = zext i32 %call64 to i64, !dbg !624
  %63 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !625
  %pos66 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %63, i32 0, i32 7, !dbg !626
  store i64 %conv65, i64* %pos66, align 8, !dbg !627
  %64 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !628
  %sequence67 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %64, i32 0, i32 0, !dbg !629
  store i32 6, i32* %sequence67, align 8, !dbg !630
  br label %sw.bb68, !dbg !628

sw.bb68:                                          ; preds = %while.body, %sw.bb62
  %65 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !631
  %pos69 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %65, i32 0, i32 7, !dbg !633
  %66 = load i64, i64* %pos69, align 8, !dbg !633
  %cmp70 = icmp ugt i64 %66, 0, !dbg !634
  br i1 %cmp70, label %if.then72, label %if.end82, !dbg !635

if.then72:                                        ; preds = %sw.bb68
  %67 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !636
  %pos73 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %67, i32 0, i32 7, !dbg !638
  %68 = load i64, i64* %pos73, align 8, !dbg !639
  %dec74 = add i64 %68, -1, !dbg !639
  store i64 %dec74, i64* %pos73, align 8, !dbg !639
  %69 = load i64*, i64** %in_pos.addr, align 8, !dbg !640
  %70 = load i64, i64* %69, align 8, !dbg !642
  %inc75 = add i64 %70, 1, !dbg !642
  store i64 %inc75, i64* %69, align 8, !dbg !642
  %71 = load i8*, i8** %in.addr, align 8, !dbg !643
  %arrayidx76 = getelementptr inbounds i8, i8* %71, i64 %70, !dbg !643
  %72 = load i8, i8* %arrayidx76, align 1, !dbg !643
  %conv77 = zext i8 %72 to i32, !dbg !643
  %cmp78 = icmp ne i32 %conv77, 0, !dbg !644
  br i1 %cmp78, label %if.then80, label %if.end81, !dbg !645

if.then80:                                        ; preds = %if.then72
  store i32 9, i32* %retval, align 4, !dbg !646
  br label %return, !dbg !646

if.end81:                                         ; preds = %if.then72
  br label %sw.epilog, !dbg !647

if.end82:                                         ; preds = %sw.bb68
  %73 = load i8*, i8** %in.addr, align 8, !dbg !648
  %74 = load i64, i64* %in_start, align 8, !dbg !649
  %add.ptr = getelementptr inbounds i8, i8* %73, i64 %74, !dbg !650
  %75 = load i64*, i64** %in_pos.addr, align 8, !dbg !651
  %76 = load i64, i64* %75, align 8, !dbg !652
  %77 = load i64, i64* %in_start, align 8, !dbg !653
  %sub = sub i64 %76, %77, !dbg !654
  %78 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !655
  %crc32 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %78, i32 0, i32 8, !dbg !656
  %79 = load i32, i32* %crc32, align 8, !dbg !656
  %call83 = call i32 @lzma_crc32(i8* %add.ptr, i64 %sub, i32 %79) #7, !dbg !657
  %80 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !658
  %crc3284 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %80, i32 0, i32 8, !dbg !659
  store i32 %call83, i32* %crc3284, align 8, !dbg !660
  %81 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !661
  %sequence85 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %81, i32 0, i32 0, !dbg !662
  store i32 7, i32* %sequence85, align 8, !dbg !663
  br label %sw.bb86, !dbg !661

sw.bb86:                                          ; preds = %while.body, %if.end82
  br label %do.body87, !dbg !664

do.body87:                                        ; preds = %do.cond, %sw.bb86
  %82 = load i64*, i64** %in_pos.addr, align 8, !dbg !665
  %83 = load i64, i64* %82, align 8, !dbg !668
  %84 = load i64, i64* %in_size.addr, align 8, !dbg !669
  %cmp88 = icmp eq i64 %83, %84, !dbg !670
  br i1 %cmp88, label %if.then90, label %if.end91, !dbg !671

if.then90:                                        ; preds = %do.body87
  store i32 0, i32* %retval, align 4, !dbg !672
  br label %return, !dbg !672

if.end91:                                         ; preds = %do.body87
  %85 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !673
  %crc3292 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %85, i32 0, i32 8, !dbg !675
  %86 = load i32, i32* %crc3292, align 8, !dbg !675
  %87 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !676
  %pos93 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %87, i32 0, i32 7, !dbg !677
  %88 = load i64, i64* %pos93, align 8, !dbg !677
  %mul = mul i64 %88, 8, !dbg !678
  %sh_prom = trunc i64 %mul to i32, !dbg !679
  %shr = lshr i32 %86, %sh_prom, !dbg !679
  %and = and i32 %shr, 255, !dbg !680
  %89 = load i64*, i64** %in_pos.addr, align 8, !dbg !681
  %90 = load i64, i64* %89, align 8, !dbg !682
  %inc94 = add i64 %90, 1, !dbg !682
  store i64 %inc94, i64* %89, align 8, !dbg !682
  %91 = load i8*, i8** %in.addr, align 8, !dbg !683
  %arrayidx95 = getelementptr inbounds i8, i8* %91, i64 %90, !dbg !683
  %92 = load i8, i8* %arrayidx95, align 1, !dbg !683
  %conv96 = zext i8 %92 to i32, !dbg !683
  %cmp97 = icmp ne i32 %and, %conv96, !dbg !684
  br i1 %cmp97, label %if.then99, label %if.end100, !dbg !685

if.then99:                                        ; preds = %if.end91
  store i32 9, i32* %retval, align 4, !dbg !686
  br label %return, !dbg !686

if.end100:                                        ; preds = %if.end91
  br label %do.cond, !dbg !687

do.cond:                                          ; preds = %if.end100
  %93 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !688
  %pos101 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %93, i32 0, i32 7, !dbg !690
  %94 = load i64, i64* %pos101, align 8, !dbg !691
  %inc102 = add i64 %94, 1, !dbg !691
  store i64 %inc102, i64* %pos101, align 8, !dbg !691
  %cmp103 = icmp ult i64 %inc102, 4, !dbg !692
  br i1 %cmp103, label %do.body87, label %do.end105, !dbg !693

do.end105:                                        ; preds = %do.cond
  %95 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !694
  %index106 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %95, i32 0, i32 2, !dbg !695
  %96 = load %struct.lzma_index_s*, %struct.lzma_index_s** %index106, align 8, !dbg !695
  %97 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !696
  %index_ptr = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %97, i32 0, i32 3, !dbg !697
  %98 = load %struct.lzma_index_s**, %struct.lzma_index_s*** %index_ptr, align 8, !dbg !697
  store %struct.lzma_index_s* %96, %struct.lzma_index_s** %98, align 8, !dbg !698
  %99 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !699
  %index107 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %99, i32 0, i32 2, !dbg !700
  store %struct.lzma_index_s* null, %struct.lzma_index_s** %index107, align 8, !dbg !701
  store i32 1, i32* %retval, align 4, !dbg !702
  br label %return, !dbg !702

sw.default:                                       ; preds = %while.body
  call void @__assert_fail(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([85 x i8], [85 x i8]* @.str.1, i32 0, i32 0), i32 196, i8* getelementptr inbounds ([163 x i8], [163 x i8]* @__PRETTY_FUNCTION__.index_decode, i32 0, i32 0)) #8, !dbg !703
  unreachable, !dbg !703

sw.epilog:                                        ; preds = %if.end81, %if.end61, %if.end17, %if.end
  br label %while.cond, !dbg !704

while.end:                                        ; preds = %while.cond
  br label %out108, !dbg !706

out108:                                           ; preds = %while.end, %if.then32, %if.then16, %if.then7
  %100 = load i8*, i8** %in.addr, align 8, !dbg !708
  %101 = load i64, i64* %in_start, align 8, !dbg !709
  %add.ptr109 = getelementptr inbounds i8, i8* %100, i64 %101, !dbg !710
  %102 = load i64*, i64** %in_pos.addr, align 8, !dbg !711
  %103 = load i64, i64* %102, align 8, !dbg !712
  %104 = load i64, i64* %in_start, align 8, !dbg !713
  %sub110 = sub i64 %103, %104, !dbg !714
  %105 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !715
  %crc32111 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %105, i32 0, i32 8, !dbg !716
  %106 = load i32, i32* %crc32111, align 8, !dbg !716
  %call112 = call i32 @lzma_crc32(i8* %add.ptr109, i64 %sub110, i32 %106) #7, !dbg !717
  %107 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !718
  %crc32113 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %107, i32 0, i32 8, !dbg !719
  store i32 %call112, i32* %crc32113, align 8, !dbg !720
  %108 = load i32, i32* %ret, align 4, !dbg !721
  store i32 %108, i32* %retval, align 4, !dbg !722
  br label %return, !dbg !722

return:                                           ; preds = %out108, %do.end105, %if.then99, %if.then90, %if.then80, %if.then54, %if.then45, %if.then
  %109 = load i32, i32* %retval, align 4, !dbg !723
  ret i32 %109, !dbg !723
}

; Function Attrs: nounwind
declare void @lzma_index_end(%struct.lzma_index_s*, %struct.lzma_allocator*) #3

; Function Attrs: nounwind
declare i64 @lzma_index_memusage(i64, i64) #3

declare void @lzma_next_end(%struct.lzma_next_coder_s*, %struct.lzma_allocator*) #2

declare noalias i8* @lzma_alloc(i64, %struct.lzma_allocator*) #2

; Function Attrs: nounwind uwtable
define internal void @index_decoder_end(%struct.lzma_coder_s* %coder, %struct.lzma_allocator* %allocator) #0 !dbg !195 {
entry:
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !724, metadata !205), !dbg !725
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !726, metadata !205), !dbg !727
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !728
  %index = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 2, !dbg !729
  %1 = load %struct.lzma_index_s*, %struct.lzma_index_s** %index, align 8, !dbg !729
  %2 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !730
  call void @lzma_index_end(%struct.lzma_index_s* %1, %struct.lzma_allocator* %2) #6, !dbg !731
  %3 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !732
  %4 = bitcast %struct.lzma_coder_s* %3 to i8*, !dbg !732
  %5 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !733
  call void @lzma_free(i8* %4, %struct.lzma_allocator* %5), !dbg !734
  ret void, !dbg !735
}

; Function Attrs: nounwind uwtable
define internal i32 @index_decoder_memconfig(%struct.lzma_coder_s* %coder, i64* %memusage, i64* %old_memlimit, i64 %new_memlimit) #0 !dbg !196 {
entry:
  %retval = alloca i32, align 4
  %coder.addr = alloca %struct.lzma_coder_s*, align 8
  %memusage.addr = alloca i64*, align 8
  %old_memlimit.addr = alloca i64*, align 8
  %new_memlimit.addr = alloca i64, align 8
  store %struct.lzma_coder_s* %coder, %struct.lzma_coder_s** %coder.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_coder_s** %coder.addr, metadata !736, metadata !205), !dbg !737
  store i64* %memusage, i64** %memusage.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %memusage.addr, metadata !738, metadata !205), !dbg !739
  store i64* %old_memlimit, i64** %old_memlimit.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %old_memlimit.addr, metadata !740, metadata !205), !dbg !741
  store i64 %new_memlimit, i64* %new_memlimit.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %new_memlimit.addr, metadata !742, metadata !205), !dbg !743
  %0 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !744
  %count = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %0, i32 0, i32 4, !dbg !745
  %1 = load i64, i64* %count, align 8, !dbg !745
  %call = call i64 @lzma_index_memusage(i64 1, i64 %1) #6, !dbg !746
  %2 = load i64*, i64** %memusage.addr, align 8, !dbg !747
  store i64 %call, i64* %2, align 8, !dbg !748
  %3 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !749
  %memlimit = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %3, i32 0, i32 1, !dbg !750
  %4 = load i64, i64* %memlimit, align 8, !dbg !750
  %5 = load i64*, i64** %old_memlimit.addr, align 8, !dbg !751
  store i64 %4, i64* %5, align 8, !dbg !752
  %6 = load i64, i64* %new_memlimit.addr, align 8, !dbg !753
  %cmp = icmp ne i64 %6, 0, !dbg !755
  br i1 %cmp, label %if.then, label %if.end4, !dbg !756

if.then:                                          ; preds = %entry
  %7 = load i64, i64* %new_memlimit.addr, align 8, !dbg !757
  %8 = load i64*, i64** %memusage.addr, align 8, !dbg !760
  %9 = load i64, i64* %8, align 8, !dbg !761
  %cmp1 = icmp ult i64 %7, %9, !dbg !762
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !763

if.then2:                                         ; preds = %if.then
  store i32 6, i32* %retval, align 4, !dbg !764
  br label %return, !dbg !764

if.end:                                           ; preds = %if.then
  %10 = load i64, i64* %new_memlimit.addr, align 8, !dbg !765
  %11 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder.addr, align 8, !dbg !766
  %memlimit3 = getelementptr inbounds %struct.lzma_coder_s, %struct.lzma_coder_s* %11, i32 0, i32 1, !dbg !767
  store i64 %10, i64* %memlimit3, align 8, !dbg !768
  br label %if.end4, !dbg !769

if.end4:                                          ; preds = %if.end, %entry
  store i32 0, i32* %retval, align 4, !dbg !770
  br label %return, !dbg !770

return:                                           ; preds = %if.end4, %if.then2
  %12 = load i32, i32* %retval, align 4, !dbg !771
  ret i32 %12, !dbg !771
}

declare void @lzma_free(i8*, %struct.lzma_allocator*) #2

; Function Attrs: nounwind
declare %struct.lzma_index_s* @lzma_index_init(%struct.lzma_allocator*) #3

; Function Attrs: nounwind
declare i32 @lzma_vli_decode(i64*, i64*, i8*, i64*, i64) #3

declare void @lzma_index_prealloc(%struct.lzma_index_s*, i64) #2

; Function Attrs: nounwind
declare i32 @lzma_index_append(%struct.lzma_index_s*, %struct.lzma_allocator*, i64, i64) #3

declare i32 @lzma_index_padding_size(%struct.lzma_index_s*) #2

; Function Attrs: nounwind readonly
declare i32 @lzma_crc32(i8*, i64, i32) #4

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #5

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind }
attributes #7 = { nounwind readonly }
attributes #8 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!201, !202}
!llvm.ident = !{!203}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !157, subprograms: !158)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/index_decoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !53, !59, !66, !154}
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
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !19, file: !1, line: 18, size: 32, align: 32, elements: !44)
!19 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !1, line: 17, size: 576, align: 64, elements: !20)
!20 = !{!21, !22, !26, !31, !33, !36, !37, !38, !41}
!21 = !DIDerivedType(tag: DW_TAG_member, name: "sequence", scope: !19, file: !1, line: 27, baseType: !18, size: 32, align: 32)
!22 = !DIDerivedType(tag: DW_TAG_member, name: "memlimit", scope: !19, file: !1, line: 30, baseType: !23, size: 64, align: 64, offset: 64)
!23 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !24, line: 55, baseType: !25)
!24 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!25 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "index", scope: !19, file: !1, line: 33, baseType: !27, size: 64, align: 64, offset: 128)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!28 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_index", file: !29, line: 37, baseType: !30)
!29 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/index.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!30 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_index_s", file: !29, line: 37, flags: DIFlagFwdDecl)
!31 = !DIDerivedType(tag: DW_TAG_member, name: "index_ptr", scope: !19, file: !1, line: 37, baseType: !32, size: 64, align: 64, offset: 192)
!32 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !27, size: 64, align: 64)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "count", scope: !19, file: !1, line: 40, baseType: !34, size: 64, align: 64, offset: 256)
!34 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !35, line: 63, baseType: !23)
!35 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!36 = !DIDerivedType(tag: DW_TAG_member, name: "unpadded_size", scope: !19, file: !1, line: 43, baseType: !34, size: 64, align: 64, offset: 320)
!37 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_size", scope: !19, file: !1, line: 46, baseType: !34, size: 64, align: 64, offset: 384)
!38 = !DIDerivedType(tag: DW_TAG_member, name: "pos", scope: !19, file: !1, line: 49, baseType: !39, size: 64, align: 64, offset: 448)
!39 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !40, line: 62, baseType: !25)
!40 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!41 = !DIDerivedType(tag: DW_TAG_member, name: "crc32", scope: !19, file: !1, line: 52, baseType: !42, size: 32, align: 32, offset: 512)
!42 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !24, line: 51, baseType: !43)
!43 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!44 = !{!45, !46, !47, !48, !49, !50, !51, !52}
!45 = !DIEnumerator(name: "SEQ_INDICATOR", value: 0)
!46 = !DIEnumerator(name: "SEQ_COUNT", value: 1)
!47 = !DIEnumerator(name: "SEQ_MEMUSAGE", value: 2)
!48 = !DIEnumerator(name: "SEQ_UNPADDED", value: 3)
!49 = !DIEnumerator(name: "SEQ_UNCOMPRESSED", value: 4)
!50 = !DIEnumerator(name: "SEQ_PADDING_INIT", value: 5)
!51 = !DIEnumerator(name: "SEQ_PADDING", value: 6)
!52 = !DIEnumerator(name: "SEQ_CRC32", value: 7)
!53 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 250, size: 32, align: 32, elements: !54)
!54 = !{!55, !56, !57, !58}
!55 = !DIEnumerator(name: "LZMA_RUN", value: 0)
!56 = !DIEnumerator(name: "LZMA_SYNC_FLUSH", value: 1)
!57 = !DIEnumerator(name: "LZMA_FULL_FLUSH", value: 2)
!58 = !DIEnumerator(name: "LZMA_FINISH", value: 3)
!59 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !60, line: 27, size: 32, align: 32, elements: !61)
!60 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!61 = !{!62, !63, !64, !65}
!62 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!63 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!64 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!65 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!66 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !68, file: !67, line: 182, size: 32, align: 32, elements: !147)
!67 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!68 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_internal_s", file: !67, line: 174, size: 704, align: 64, elements: !69)
!69 = !{!70, !139, !140, !141, !146}
!70 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !68, file: !67, line: 176, baseType: !71, size: 512, align: 64)
!71 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !67, line: 75, baseType: !72)
!72 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !67, line: 119, size: 512, align: 64, elements: !73)
!73 = !{!74, !77, !78, !80, !110, !115, !122, !127}
!74 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !72, file: !67, line: 121, baseType: !75, size: 64, align: 64)
!75 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !76, size: 64, align: 64)
!76 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !67, line: 73, baseType: !19)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !72, file: !67, line: 125, baseType: !34, size: 64, align: 64, offset: 64)
!78 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !72, file: !67, line: 131, baseType: !79, size: 64, align: 64, offset: 128)
!79 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !24, line: 122, baseType: !25)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !72, file: !67, line: 134, baseType: !81, size: 64, align: 64, offset: 192)
!81 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !67, line: 89, baseType: !82)
!82 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !83, size: 64, align: 64)
!83 = !DISubroutineType(types: !84)
!84 = !{!85, !75, !86, !100, !105, !39, !107, !105, !39, !109}
!85 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!86 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !87, size: 64, align: 64)
!87 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !88)
!88 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !89)
!89 = !{!90, !95, !99}
!90 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !88, file: !4, line: 376, baseType: !91, size: 64, align: 64)
!91 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !92, size: 64, align: 64)
!92 = !DISubroutineType(types: !93)
!93 = !{!94, !94, !39, !39}
!94 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !88, file: !4, line: 390, baseType: !96, size: 64, align: 64, offset: 64)
!96 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !97, size: 64, align: 64)
!97 = !DISubroutineType(types: !98)
!98 = !{null, !94, !94}
!99 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !88, file: !4, line: 401, baseType: !94, size: 64, align: 64, offset: 128)
!100 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !101)
!101 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !102, size: 64, align: 64)
!102 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !103)
!103 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !24, line: 48, baseType: !104)
!104 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!105 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !106)
!106 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !39, size: 64, align: 64)
!107 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !108)
!108 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !103, size: 64, align: 64)
!109 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !53)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !72, file: !67, line: 139, baseType: !111, size: 64, align: 64, offset: 256)
!111 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !67, line: 97, baseType: !112)
!112 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !113, size: 64, align: 64)
!113 = !DISubroutineType(types: !114)
!114 = !{null, !75, !86}
!115 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !72, file: !67, line: 143, baseType: !116, size: 64, align: 64, offset: 320)
!116 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !117, size: 64, align: 64)
!117 = !DISubroutineType(types: !118)
!118 = !{!119, !120}
!119 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !60, line: 55, baseType: !59)
!120 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !121, size: 64, align: 64)
!121 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !76)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !72, file: !67, line: 147, baseType: !123, size: 64, align: 64, offset: 384)
!123 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !124, size: 64, align: 64)
!124 = !DISubroutineType(types: !125)
!125 = !{!85, !75, !126, !126, !23}
!126 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !23, size: 64, align: 64)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !72, file: !67, line: 152, baseType: !128, size: 64, align: 64, offset: 448)
!128 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !129, size: 64, align: 64)
!129 = !DISubroutineType(types: !130)
!130 = !{!85, !75, !86, !131, !131}
!131 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !132, size: 64, align: 64)
!132 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !133)
!133 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !134, line: 65, baseType: !135)
!134 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!135 = !DICompositeType(tag: DW_TAG_structure_type, file: !134, line: 43, size: 128, align: 64, elements: !136)
!136 = !{!137, !138}
!137 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !135, file: !134, line: 54, baseType: !34, size: 64, align: 64)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !135, file: !134, line: 63, baseType: !94, size: 64, align: 64, offset: 64)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "sequence", scope: !68, file: !67, line: 189, baseType: !66, size: 32, align: 32, offset: 512)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !68, file: !67, line: 194, baseType: !39, size: 64, align: 64, offset: 576)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "supported_actions", scope: !68, file: !67, line: 197, baseType: !142, size: 32, align: 8, offset: 640)
!142 = !DICompositeType(tag: DW_TAG_array_type, baseType: !143, size: 32, align: 8, elements: !144)
!143 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!144 = !{!145}
!145 = !DISubrange(count: 4)
!146 = !DIDerivedType(tag: DW_TAG_member, name: "allow_buf_error", scope: !68, file: !67, line: 201, baseType: !143, size: 8, align: 8, offset: 672)
!147 = !{!148, !149, !150, !151, !152, !153}
!148 = !DIEnumerator(name: "ISEQ_RUN", value: 0)
!149 = !DIEnumerator(name: "ISEQ_SYNC_FLUSH", value: 1)
!150 = !DIEnumerator(name: "ISEQ_FULL_FLUSH", value: 2)
!151 = !DIEnumerator(name: "ISEQ_FINISH", value: 3)
!152 = !DIEnumerator(name: "ISEQ_END", value: 4)
!153 = !DIEnumerator(name: "ISEQ_ERROR", value: 5)
!154 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 44, size: 32, align: 32, elements: !155)
!155 = !{!156}
!156 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!157 = !{!94, !79}
!158 = !{!159, !188, !191, !195, !196, !197, !200}
!159 = distinct !DISubprogram(name: "lzma_index_decoder", scope: !1, file: !1, line: 290, type: !160, isLocal: false, isDefinition: true, scopeLine: 291, flags: DIFlagPrototyped, isOptimized: false, variables: !187)
!160 = !DISubroutineType(types: !161)
!161 = !{!85, !162, !32, !23}
!162 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !163, size: 64, align: 64)
!163 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_stream", file: !4, line: 490, baseType: !164)
!164 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 453, size: 1088, align: 64, elements: !165)
!165 = !{!166, !167, !168, !169, !170, !171, !172, !173, !176, !177, !178, !179, !180, !181, !182, !183, !184, !186}
!166 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !164, file: !4, line: 454, baseType: !101, size: 64, align: 64)
!167 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !164, file: !4, line: 455, baseType: !39, size: 64, align: 64, offset: 64)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !164, file: !4, line: 456, baseType: !23, size: 64, align: 64, offset: 128)
!169 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !164, file: !4, line: 458, baseType: !108, size: 64, align: 64, offset: 192)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !164, file: !4, line: 459, baseType: !39, size: 64, align: 64, offset: 256)
!171 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !164, file: !4, line: 460, baseType: !23, size: 64, align: 64, offset: 320)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "allocator", scope: !164, file: !4, line: 468, baseType: !86, size: 64, align: 64, offset: 384)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "internal", scope: !164, file: !4, line: 471, baseType: !174, size: 64, align: 64, offset: 448)
!174 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !175, size: 64, align: 64)
!175 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_internal", file: !4, line: 411, baseType: !68)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !164, file: !4, line: 479, baseType: !94, size: 64, align: 64, offset: 512)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !164, file: !4, line: 480, baseType: !94, size: 64, align: 64, offset: 576)
!178 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !164, file: !4, line: 481, baseType: !94, size: 64, align: 64, offset: 640)
!179 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr4", scope: !164, file: !4, line: 482, baseType: !94, size: 64, align: 64, offset: 704)
!180 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !164, file: !4, line: 483, baseType: !23, size: 64, align: 64, offset: 768)
!181 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !164, file: !4, line: 484, baseType: !23, size: 64, align: 64, offset: 832)
!182 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !164, file: !4, line: 485, baseType: !39, size: 64, align: 64, offset: 896)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !164, file: !4, line: 486, baseType: !39, size: 64, align: 64, offset: 960)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !164, file: !4, line: 487, baseType: !185, size: 32, align: 32, offset: 1024)
!185 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !154)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !164, file: !4, line: 488, baseType: !185, size: 32, align: 32, offset: 1056)
!187 = !{}
!188 = distinct !DISubprogram(name: "lzma_index_buffer_decode", scope: !1, file: !1, line: 302, type: !189, isLocal: false, isDefinition: true, scopeLine: 305, flags: DIFlagPrototyped, isOptimized: false, variables: !187)
!189 = !DISubroutineType(types: !190)
!190 = !{!85, !32, !126, !86, !101, !106, !39}
!191 = distinct !DISubprogram(name: "index_decoder_init", scope: !1, file: !1, line: 264, type: !192, isLocal: true, isDefinition: true, scopeLine: 266, flags: DIFlagPrototyped, isOptimized: false, variables: !187)
!192 = !DISubroutineType(types: !193)
!193 = !{!85, !194, !86, !32, !23}
!194 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !71, size: 64, align: 64)
!195 = distinct !DISubprogram(name: "index_decoder_end", scope: !1, file: !1, line: 210, type: !113, isLocal: true, isDefinition: true, scopeLine: 211, flags: DIFlagPrototyped, isOptimized: false, variables: !187)
!196 = distinct !DISubprogram(name: "index_decoder_memconfig", scope: !1, file: !1, line: 219, type: !124, isLocal: true, isDefinition: true, scopeLine: 221, flags: DIFlagPrototyped, isOptimized: false, variables: !187)
!197 = distinct !DISubprogram(name: "index_decoder_reset", scope: !1, file: !1, line: 237, type: !198, isLocal: true, isDefinition: true, scopeLine: 239, flags: DIFlagPrototyped, isOptimized: false, variables: !187)
!198 = !DISubroutineType(types: !199)
!199 = !{!85, !75, !86, !32, !23}
!200 = distinct !DISubprogram(name: "index_decode", scope: !1, file: !1, line: 57, type: !83, isLocal: true, isDefinition: true, scopeLine: 64, flags: DIFlagPrototyped, isOptimized: false, variables: !187)
!201 = !{i32 2, !"Dwarf Version", i32 4}
!202 = !{i32 2, !"Debug Info Version", i32 3}
!203 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!204 = !DILocalVariable(name: "strm", arg: 1, scope: !159, file: !1, line: 290, type: !162)
!205 = !DIExpression()
!206 = !DILocation(line: 290, column: 33, scope: !159)
!207 = !DILocalVariable(name: "i", arg: 2, scope: !159, file: !1, line: 290, type: !32)
!208 = !DILocation(line: 290, column: 52, scope: !159)
!209 = !DILocalVariable(name: "memlimit", arg: 3, scope: !159, file: !1, line: 290, type: !23)
!210 = !DILocation(line: 290, column: 64, scope: !159)
!211 = !DILocation(line: 292, column: 2, scope: !159)
!212 = !DILocalVariable(name: "ret_", scope: !213, file: !1, line: 292, type: !85)
!213 = distinct !DILexicalBlock(scope: !159, file: !1, line: 292, column: 2)
!214 = !DILocation(line: 292, column: 2, scope: !213)
!215 = !DILocation(line: 292, column: 2, scope: !216)
!216 = !DILexicalBlockFile(scope: !213, file: !1, discriminator: 1)
!217 = !DILocalVariable(name: "ret_", scope: !218, file: !1, line: 292, type: !219)
!218 = distinct !DILexicalBlock(scope: !213, file: !1, line: 292, column: 2)
!219 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !85)
!220 = !DILocation(line: 292, column: 2, scope: !218)
!221 = !DILocation(line: 292, column: 2, scope: !222)
!222 = !DILexicalBlockFile(scope: !218, file: !1, discriminator: 2)
!223 = !DILocation(line: 292, column: 2, scope: !224)
!224 = !DILexicalBlockFile(scope: !225, file: !1, discriminator: 3)
!225 = distinct !DILexicalBlock(scope: !218, file: !1, line: 292, column: 2)
!226 = !DILocation(line: 292, column: 2, scope: !227)
!227 = !DILexicalBlockFile(scope: !218, file: !1, discriminator: 4)
!228 = !DILocation(line: 292, column: 2, scope: !229)
!229 = !DILexicalBlockFile(scope: !213, file: !1, discriminator: 5)
!230 = !DILocation(line: 292, column: 2, scope: !231)
!231 = !DILexicalBlockFile(scope: !232, file: !1, discriminator: 6)
!232 = distinct !DILexicalBlock(scope: !233, file: !1, line: 292, column: 2)
!233 = distinct !DILexicalBlock(scope: !213, file: !1, line: 292, column: 2)
!234 = !DILocation(line: 292, column: 2, scope: !235)
!235 = !DILexicalBlockFile(scope: !213, file: !1, discriminator: 7)
!236 = !DILocation(line: 294, column: 2, scope: !159)
!237 = !DILocation(line: 294, column: 8, scope: !159)
!238 = !DILocation(line: 294, column: 18, scope: !159)
!239 = !DILocation(line: 294, column: 46, scope: !159)
!240 = !DILocation(line: 295, column: 2, scope: !159)
!241 = !DILocation(line: 295, column: 8, scope: !159)
!242 = !DILocation(line: 295, column: 18, scope: !159)
!243 = !DILocation(line: 295, column: 49, scope: !159)
!244 = !DILocation(line: 297, column: 2, scope: !159)
!245 = !DILocation(line: 298, column: 1, scope: !159)
!246 = !DILocalVariable(name: "next", arg: 1, scope: !191, file: !1, line: 264, type: !194)
!247 = !DILocation(line: 264, column: 37, scope: !191)
!248 = !DILocalVariable(name: "allocator", arg: 2, scope: !191, file: !1, line: 264, type: !86)
!249 = !DILocation(line: 264, column: 59, scope: !191)
!250 = !DILocalVariable(name: "i", arg: 3, scope: !191, file: !1, line: 265, type: !32)
!251 = !DILocation(line: 265, column: 16, scope: !191)
!252 = !DILocalVariable(name: "memlimit", arg: 4, scope: !191, file: !1, line: 265, type: !23)
!253 = !DILocation(line: 265, column: 28, scope: !191)
!254 = !DILocation(line: 267, column: 2, scope: !191)
!255 = !DILocation(line: 267, column: 2, scope: !256)
!256 = !DILexicalBlockFile(scope: !257, file: !1, discriminator: 1)
!257 = distinct !DILexicalBlock(scope: !258, file: !1, line: 267, column: 2)
!258 = distinct !DILexicalBlock(scope: !191, file: !1, line: 267, column: 2)
!259 = !DILocation(line: 267, column: 2, scope: !260)
!260 = !DILexicalBlockFile(scope: !257, file: !1, discriminator: 2)
!261 = !DILocation(line: 267, column: 2, scope: !262)
!262 = !DILexicalBlockFile(scope: !258, file: !1, discriminator: 3)
!263 = !DILocation(line: 269, column: 6, scope: !264)
!264 = distinct !DILexicalBlock(scope: !191, file: !1, line: 269, column: 6)
!265 = !DILocation(line: 269, column: 8, scope: !264)
!266 = !DILocation(line: 269, column: 16, scope: !264)
!267 = !DILocation(line: 269, column: 19, scope: !268)
!268 = !DILexicalBlockFile(scope: !264, file: !1, discriminator: 1)
!269 = !DILocation(line: 269, column: 28, scope: !268)
!270 = !DILocation(line: 269, column: 6, scope: !268)
!271 = !DILocation(line: 270, column: 3, scope: !264)
!272 = !DILocation(line: 272, column: 6, scope: !273)
!273 = distinct !DILexicalBlock(scope: !191, file: !1, line: 272, column: 6)
!274 = !DILocation(line: 272, column: 12, scope: !273)
!275 = !DILocation(line: 272, column: 18, scope: !273)
!276 = !DILocation(line: 272, column: 6, scope: !191)
!277 = !DILocation(line: 273, column: 48, scope: !278)
!278 = distinct !DILexicalBlock(scope: !273, file: !1, line: 272, column: 27)
!279 = !DILocation(line: 273, column: 17, scope: !278)
!280 = !DILocation(line: 273, column: 3, scope: !278)
!281 = !DILocation(line: 273, column: 9, scope: !278)
!282 = !DILocation(line: 273, column: 15, scope: !278)
!283 = !DILocation(line: 274, column: 7, scope: !284)
!284 = distinct !DILexicalBlock(scope: !278, file: !1, line: 274, column: 7)
!285 = !DILocation(line: 274, column: 13, scope: !284)
!286 = !DILocation(line: 274, column: 19, scope: !284)
!287 = !DILocation(line: 274, column: 7, scope: !278)
!288 = !DILocation(line: 275, column: 4, scope: !284)
!289 = !DILocation(line: 277, column: 3, scope: !278)
!290 = !DILocation(line: 277, column: 9, scope: !278)
!291 = !DILocation(line: 277, column: 14, scope: !278)
!292 = !DILocation(line: 278, column: 3, scope: !278)
!293 = !DILocation(line: 278, column: 9, scope: !278)
!294 = !DILocation(line: 278, column: 13, scope: !278)
!295 = !DILocation(line: 279, column: 3, scope: !278)
!296 = !DILocation(line: 279, column: 9, scope: !278)
!297 = !DILocation(line: 279, column: 19, scope: !278)
!298 = !DILocation(line: 280, column: 3, scope: !278)
!299 = !DILocation(line: 280, column: 9, scope: !278)
!300 = !DILocation(line: 280, column: 16, scope: !278)
!301 = !DILocation(line: 280, column: 22, scope: !278)
!302 = !DILocation(line: 281, column: 2, scope: !278)
!303 = !DILocation(line: 282, column: 18, scope: !304)
!304 = distinct !DILexicalBlock(scope: !273, file: !1, line: 281, column: 9)
!305 = !DILocation(line: 282, column: 24, scope: !304)
!306 = !DILocation(line: 282, column: 31, scope: !304)
!307 = !DILocation(line: 282, column: 38, scope: !304)
!308 = !DILocation(line: 282, column: 3, scope: !304)
!309 = !DILocation(line: 285, column: 29, scope: !191)
!310 = !DILocation(line: 285, column: 35, scope: !191)
!311 = !DILocation(line: 285, column: 42, scope: !191)
!312 = !DILocation(line: 285, column: 53, scope: !191)
!313 = !DILocation(line: 285, column: 56, scope: !191)
!314 = !DILocation(line: 285, column: 9, scope: !191)
!315 = !DILocation(line: 285, column: 2, scope: !191)
!316 = !DILocation(line: 286, column: 1, scope: !191)
!317 = !DILocalVariable(name: "i", arg: 1, scope: !188, file: !1, line: 303, type: !32)
!318 = !DILocation(line: 303, column: 16, scope: !188)
!319 = !DILocalVariable(name: "memlimit", arg: 2, scope: !188, file: !1, line: 303, type: !126)
!320 = !DILocation(line: 303, column: 29, scope: !188)
!321 = !DILocalVariable(name: "allocator", arg: 3, scope: !188, file: !1, line: 303, type: !86)
!322 = !DILocation(line: 303, column: 55, scope: !188)
!323 = !DILocalVariable(name: "in", arg: 4, scope: !188, file: !1, line: 304, type: !101)
!324 = !DILocation(line: 304, column: 18, scope: !188)
!325 = !DILocalVariable(name: "in_pos", arg: 5, scope: !188, file: !1, line: 304, type: !106)
!326 = !DILocation(line: 304, column: 30, scope: !188)
!327 = !DILocalVariable(name: "in_size", arg: 6, scope: !188, file: !1, line: 304, type: !39)
!328 = !DILocation(line: 304, column: 45, scope: !188)
!329 = !DILocalVariable(name: "coder", scope: !188, file: !1, line: 306, type: !76)
!330 = !DILocation(line: 306, column: 13, scope: !188)
!331 = !DILocalVariable(name: "ret", scope: !188, file: !1, line: 307, type: !85)
!332 = !DILocation(line: 307, column: 11, scope: !188)
!333 = !DILocalVariable(name: "in_start", scope: !188, file: !1, line: 311, type: !334)
!334 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !39)
!335 = !DILocation(line: 311, column: 15, scope: !188)
!336 = !DILocation(line: 311, column: 27, scope: !188)
!337 = !DILocation(line: 311, column: 26, scope: !188)
!338 = !DILocation(line: 314, column: 6, scope: !339)
!339 = distinct !DILexicalBlock(scope: !188, file: !1, line: 314, column: 6)
!340 = !DILocation(line: 314, column: 8, scope: !339)
!341 = !DILocation(line: 314, column: 16, scope: !339)
!342 = !DILocation(line: 314, column: 19, scope: !343)
!343 = !DILexicalBlockFile(scope: !339, file: !1, discriminator: 1)
!344 = !DILocation(line: 314, column: 28, scope: !343)
!345 = !DILocation(line: 315, column: 4, scope: !339)
!346 = !DILocation(line: 315, column: 7, scope: !343)
!347 = !DILocation(line: 315, column: 10, scope: !343)
!348 = !DILocation(line: 315, column: 18, scope: !343)
!349 = !DILocation(line: 315, column: 21, scope: !350)
!350 = !DILexicalBlockFile(scope: !339, file: !1, discriminator: 2)
!351 = !DILocation(line: 315, column: 28, scope: !350)
!352 = !DILocation(line: 315, column: 36, scope: !350)
!353 = !DILocation(line: 315, column: 40, scope: !354)
!354 = !DILexicalBlockFile(scope: !339, file: !1, discriminator: 3)
!355 = !DILocation(line: 315, column: 39, scope: !354)
!356 = !DILocation(line: 315, column: 49, scope: !354)
!357 = !DILocation(line: 315, column: 47, scope: !354)
!358 = !DILocation(line: 314, column: 6, scope: !359)
!359 = !DILexicalBlockFile(scope: !188, file: !1, discriminator: 2)
!360 = !DILocation(line: 316, column: 3, scope: !339)
!361 = !DILocation(line: 319, column: 2, scope: !188)
!362 = !DILocalVariable(name: "ret_", scope: !363, file: !1, line: 319, type: !219)
!363 = distinct !DILexicalBlock(scope: !188, file: !1, line: 319, column: 2)
!364 = !DILocation(line: 319, column: 2, scope: !363)
!365 = !DILocation(line: 319, column: 2, scope: !366)
!366 = !DILexicalBlockFile(scope: !363, file: !1, discriminator: 1)
!367 = !DILocation(line: 319, column: 2, scope: !368)
!368 = !DILexicalBlockFile(scope: !369, file: !1, discriminator: 2)
!369 = distinct !DILexicalBlock(scope: !363, file: !1, line: 319, column: 2)
!370 = !DILocation(line: 319, column: 2, scope: !371)
!371 = !DILexicalBlockFile(scope: !363, file: !1, discriminator: 3)
!372 = !DILocation(line: 322, column: 29, scope: !188)
!373 = !DILocation(line: 322, column: 40, scope: !188)
!374 = !DILocation(line: 322, column: 44, scope: !188)
!375 = !DILocation(line: 322, column: 52, scope: !188)
!376 = !DILocation(line: 322, column: 8, scope: !188)
!377 = !DILocation(line: 322, column: 6, scope: !188)
!378 = !DILocation(line: 325, column: 6, scope: !379)
!379 = distinct !DILexicalBlock(scope: !188, file: !1, line: 325, column: 6)
!380 = !DILocation(line: 325, column: 10, scope: !379)
!381 = !DILocation(line: 325, column: 6, scope: !188)
!382 = !DILocation(line: 326, column: 7, scope: !383)
!383 = distinct !DILexicalBlock(scope: !379, file: !1, line: 325, column: 30)
!384 = !DILocation(line: 327, column: 2, scope: !383)
!385 = !DILocation(line: 330, column: 24, scope: !386)
!386 = distinct !DILexicalBlock(scope: !379, file: !1, line: 327, column: 9)
!387 = !DILocation(line: 330, column: 31, scope: !386)
!388 = !DILocation(line: 330, column: 3, scope: !386)
!389 = !DILocation(line: 331, column: 13, scope: !386)
!390 = !DILocation(line: 331, column: 4, scope: !386)
!391 = !DILocation(line: 331, column: 11, scope: !386)
!392 = !DILocation(line: 333, column: 7, scope: !393)
!393 = distinct !DILexicalBlock(scope: !386, file: !1, line: 333, column: 7)
!394 = !DILocation(line: 333, column: 11, scope: !393)
!395 = !DILocation(line: 333, column: 7, scope: !386)
!396 = !DILocation(line: 337, column: 8, scope: !397)
!397 = distinct !DILexicalBlock(scope: !393, file: !1, line: 333, column: 23)
!398 = !DILocation(line: 339, column: 3, scope: !397)
!399 = !DILocation(line: 339, column: 14, scope: !400)
!400 = !DILexicalBlockFile(scope: !401, file: !1, discriminator: 1)
!401 = distinct !DILexicalBlock(scope: !393, file: !1, line: 339, column: 14)
!402 = !DILocation(line: 339, column: 18, scope: !400)
!403 = !DILocation(line: 342, column: 45, scope: !404)
!404 = distinct !DILexicalBlock(scope: !401, file: !1, line: 339, column: 42)
!405 = !DILocation(line: 342, column: 16, scope: !404)
!406 = !DILocation(line: 342, column: 5, scope: !404)
!407 = !DILocation(line: 342, column: 14, scope: !404)
!408 = !DILocation(line: 343, column: 3, scope: !404)
!409 = !DILocation(line: 346, column: 9, scope: !188)
!410 = !DILocation(line: 346, column: 2, scope: !188)
!411 = !DILocation(line: 347, column: 1, scope: !188)
!412 = !DILocalVariable(name: "coder", arg: 1, scope: !197, file: !1, line: 237, type: !75)
!413 = !DILocation(line: 237, column: 33, scope: !197)
!414 = !DILocalVariable(name: "allocator", arg: 2, scope: !197, file: !1, line: 237, type: !86)
!415 = !DILocation(line: 237, column: 56, scope: !197)
!416 = !DILocalVariable(name: "i", arg: 3, scope: !197, file: !1, line: 238, type: !32)
!417 = !DILocation(line: 238, column: 16, scope: !197)
!418 = !DILocalVariable(name: "memlimit", arg: 4, scope: !197, file: !1, line: 238, type: !23)
!419 = !DILocation(line: 238, column: 28, scope: !197)
!420 = !DILocation(line: 244, column: 21, scope: !197)
!421 = !DILocation(line: 244, column: 2, scope: !197)
!422 = !DILocation(line: 244, column: 9, scope: !197)
!423 = !DILocation(line: 244, column: 19, scope: !197)
!424 = !DILocation(line: 245, column: 3, scope: !197)
!425 = !DILocation(line: 245, column: 5, scope: !197)
!426 = !DILocation(line: 248, column: 33, scope: !197)
!427 = !DILocation(line: 248, column: 17, scope: !197)
!428 = !DILocation(line: 248, column: 2, scope: !197)
!429 = !DILocation(line: 248, column: 9, scope: !197)
!430 = !DILocation(line: 248, column: 15, scope: !197)
!431 = !DILocation(line: 249, column: 6, scope: !432)
!432 = distinct !DILexicalBlock(scope: !197, file: !1, line: 249, column: 6)
!433 = !DILocation(line: 249, column: 13, scope: !432)
!434 = !DILocation(line: 249, column: 19, scope: !432)
!435 = !DILocation(line: 249, column: 6, scope: !197)
!436 = !DILocation(line: 250, column: 3, scope: !432)
!437 = !DILocation(line: 253, column: 2, scope: !197)
!438 = !DILocation(line: 253, column: 9, scope: !197)
!439 = !DILocation(line: 253, column: 18, scope: !197)
!440 = !DILocation(line: 254, column: 20, scope: !197)
!441 = !DILocation(line: 254, column: 2, scope: !197)
!442 = !DILocation(line: 254, column: 9, scope: !197)
!443 = !DILocation(line: 254, column: 18, scope: !197)
!444 = !DILocation(line: 255, column: 2, scope: !197)
!445 = !DILocation(line: 255, column: 9, scope: !197)
!446 = !DILocation(line: 255, column: 15, scope: !197)
!447 = !DILocation(line: 256, column: 2, scope: !197)
!448 = !DILocation(line: 256, column: 9, scope: !197)
!449 = !DILocation(line: 256, column: 13, scope: !197)
!450 = !DILocation(line: 257, column: 2, scope: !197)
!451 = !DILocation(line: 257, column: 9, scope: !197)
!452 = !DILocation(line: 257, column: 15, scope: !197)
!453 = !DILocation(line: 259, column: 2, scope: !197)
!454 = !DILocation(line: 260, column: 1, scope: !197)
!455 = !DILocalVariable(name: "coder", arg: 1, scope: !200, file: !1, line: 57, type: !75)
!456 = !DILocation(line: 57, column: 26, scope: !200)
!457 = !DILocalVariable(name: "allocator", arg: 2, scope: !200, file: !1, line: 57, type: !86)
!458 = !DILocation(line: 57, column: 49, scope: !200)
!459 = !DILocalVariable(name: "in", arg: 3, scope: !200, file: !1, line: 58, type: !100)
!460 = !DILocation(line: 58, column: 32, scope: !200)
!461 = !DILocalVariable(name: "in_pos", arg: 4, scope: !200, file: !1, line: 58, type: !105)
!462 = !DILocation(line: 58, column: 58, scope: !200)
!463 = !DILocalVariable(name: "in_size", arg: 5, scope: !200, file: !1, line: 59, type: !39)
!464 = !DILocation(line: 59, column: 10, scope: !200)
!465 = !DILocalVariable(name: "out", arg: 6, scope: !200, file: !1, line: 60, type: !107)
!466 = !DILocation(line: 60, column: 26, scope: !200)
!467 = !DILocalVariable(name: "out_pos", arg: 7, scope: !200, file: !1, line: 61, type: !105)
!468 = !DILocation(line: 61, column: 25, scope: !200)
!469 = !DILocalVariable(name: "out_size", arg: 8, scope: !200, file: !1, line: 62, type: !39)
!470 = !DILocation(line: 62, column: 10, scope: !200)
!471 = !DILocalVariable(name: "action", arg: 9, scope: !200, file: !1, line: 63, type: !109)
!472 = !DILocation(line: 63, column: 15, scope: !200)
!473 = !DILocalVariable(name: "in_start", scope: !200, file: !1, line: 66, type: !334)
!474 = !DILocation(line: 66, column: 15, scope: !200)
!475 = !DILocation(line: 66, column: 27, scope: !200)
!476 = !DILocation(line: 66, column: 26, scope: !200)
!477 = !DILocalVariable(name: "ret", scope: !200, file: !1, line: 67, type: !85)
!478 = !DILocation(line: 67, column: 11, scope: !200)
!479 = !DILocation(line: 69, column: 2, scope: !200)
!480 = !DILocation(line: 69, column: 10, scope: !481)
!481 = !DILexicalBlockFile(scope: !200, file: !1, discriminator: 1)
!482 = !DILocation(line: 69, column: 9, scope: !481)
!483 = !DILocation(line: 69, column: 19, scope: !481)
!484 = !DILocation(line: 69, column: 17, scope: !481)
!485 = !DILocation(line: 69, column: 2, scope: !481)
!486 = !DILocation(line: 70, column: 10, scope: !200)
!487 = !DILocation(line: 70, column: 17, scope: !200)
!488 = !DILocation(line: 70, column: 2, scope: !200)
!489 = !DILocation(line: 81, column: 12, scope: !490)
!490 = distinct !DILexicalBlock(scope: !491, file: !1, line: 81, column: 7)
!491 = distinct !DILexicalBlock(scope: !200, file: !1, line: 70, column: 27)
!492 = !DILocation(line: 81, column: 19, scope: !490)
!493 = !DILocation(line: 81, column: 7, scope: !490)
!494 = !DILocation(line: 81, column: 23, scope: !490)
!495 = !DILocation(line: 81, column: 7, scope: !491)
!496 = !DILocation(line: 82, column: 4, scope: !490)
!497 = !DILocation(line: 84, column: 3, scope: !491)
!498 = !DILocation(line: 84, column: 10, scope: !491)
!499 = !DILocation(line: 84, column: 19, scope: !491)
!500 = !DILocation(line: 85, column: 3, scope: !491)
!501 = !DILocation(line: 88, column: 26, scope: !491)
!502 = !DILocation(line: 88, column: 33, scope: !491)
!503 = !DILocation(line: 88, column: 41, scope: !491)
!504 = !DILocation(line: 88, column: 48, scope: !491)
!505 = !DILocation(line: 89, column: 5, scope: !491)
!506 = !DILocation(line: 89, column: 9, scope: !491)
!507 = !DILocation(line: 89, column: 17, scope: !491)
!508 = !DILocation(line: 88, column: 9, scope: !491)
!509 = !DILocation(line: 88, column: 7, scope: !491)
!510 = !DILocation(line: 90, column: 7, scope: !511)
!511 = distinct !DILexicalBlock(scope: !491, file: !1, line: 90, column: 7)
!512 = !DILocation(line: 90, column: 11, scope: !511)
!513 = !DILocation(line: 90, column: 7, scope: !491)
!514 = !DILocation(line: 91, column: 4, scope: !511)
!515 = !DILocation(line: 93, column: 3, scope: !491)
!516 = !DILocation(line: 93, column: 10, scope: !491)
!517 = !DILocation(line: 93, column: 14, scope: !491)
!518 = !DILocation(line: 94, column: 3, scope: !491)
!519 = !DILocation(line: 94, column: 10, scope: !491)
!520 = !DILocation(line: 94, column: 19, scope: !491)
!521 = !DILocation(line: 99, column: 30, scope: !522)
!522 = distinct !DILexicalBlock(scope: !491, file: !1, line: 99, column: 7)
!523 = !DILocation(line: 99, column: 37, scope: !522)
!524 = !DILocation(line: 99, column: 7, scope: !522)
!525 = !DILocation(line: 99, column: 46, scope: !522)
!526 = !DILocation(line: 99, column: 53, scope: !522)
!527 = !DILocation(line: 99, column: 44, scope: !522)
!528 = !DILocation(line: 99, column: 7, scope: !491)
!529 = !DILocation(line: 100, column: 8, scope: !530)
!530 = distinct !DILexicalBlock(scope: !522, file: !1, line: 99, column: 63)
!531 = !DILocation(line: 101, column: 4, scope: !530)
!532 = !DILocation(line: 106, column: 23, scope: !491)
!533 = !DILocation(line: 106, column: 30, scope: !491)
!534 = !DILocation(line: 106, column: 37, scope: !491)
!535 = !DILocation(line: 106, column: 44, scope: !491)
!536 = !DILocation(line: 106, column: 3, scope: !491)
!537 = !DILocation(line: 108, column: 7, scope: !491)
!538 = !DILocation(line: 109, column: 21, scope: !491)
!539 = !DILocation(line: 109, column: 28, scope: !491)
!540 = !DILocation(line: 109, column: 34, scope: !491)
!541 = !DILocation(line: 109, column: 3, scope: !491)
!542 = !DILocation(line: 109, column: 10, scope: !491)
!543 = !DILocation(line: 109, column: 19, scope: !491)
!544 = !DILocation(line: 111, column: 3, scope: !491)
!545 = !DILocalVariable(name: "size", scope: !546, file: !1, line: 115, type: !547)
!546 = distinct !DILexicalBlock(scope: !491, file: !1, line: 114, column: 25)
!547 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !34, size: 64, align: 64)
!548 = !DILocation(line: 115, column: 13, scope: !546)
!549 = !DILocation(line: 115, column: 20, scope: !546)
!550 = !DILocation(line: 115, column: 27, scope: !546)
!551 = !DILocation(line: 115, column: 36, scope: !546)
!552 = !DILocation(line: 116, column: 8, scope: !546)
!553 = !DILocation(line: 116, column: 15, scope: !546)
!554 = !DILocation(line: 115, column: 20, scope: !555)
!555 = !DILexicalBlockFile(scope: !546, file: !1, discriminator: 1)
!556 = !DILocation(line: 117, column: 8, scope: !546)
!557 = !DILocation(line: 117, column: 15, scope: !546)
!558 = !DILocation(line: 115, column: 20, scope: !559)
!559 = !DILexicalBlockFile(scope: !546, file: !1, discriminator: 2)
!560 = !DILocation(line: 115, column: 20, scope: !561)
!561 = !DILexicalBlockFile(scope: !546, file: !1, discriminator: 3)
!562 = !DILocation(line: 115, column: 13, scope: !561)
!563 = !DILocation(line: 119, column: 25, scope: !546)
!564 = !DILocation(line: 119, column: 32, scope: !546)
!565 = !DILocation(line: 119, column: 39, scope: !546)
!566 = !DILocation(line: 120, column: 5, scope: !546)
!567 = !DILocation(line: 120, column: 9, scope: !546)
!568 = !DILocation(line: 120, column: 17, scope: !546)
!569 = !DILocation(line: 119, column: 9, scope: !546)
!570 = !DILocation(line: 119, column: 7, scope: !546)
!571 = !DILocation(line: 121, column: 7, scope: !572)
!572 = distinct !DILexicalBlock(scope: !546, file: !1, line: 121, column: 7)
!573 = !DILocation(line: 121, column: 11, scope: !572)
!574 = !DILocation(line: 121, column: 7, scope: !546)
!575 = !DILocation(line: 122, column: 4, scope: !572)
!576 = !DILocation(line: 124, column: 7, scope: !546)
!577 = !DILocation(line: 125, column: 3, scope: !546)
!578 = !DILocation(line: 125, column: 10, scope: !546)
!579 = !DILocation(line: 125, column: 14, scope: !546)
!580 = !DILocation(line: 127, column: 7, scope: !581)
!581 = distinct !DILexicalBlock(scope: !546, file: !1, line: 127, column: 7)
!582 = !DILocation(line: 127, column: 14, scope: !581)
!583 = !DILocation(line: 127, column: 23, scope: !581)
!584 = !DILocation(line: 127, column: 7, scope: !546)
!585 = !DILocation(line: 130, column: 8, scope: !586)
!586 = distinct !DILexicalBlock(scope: !587, file: !1, line: 130, column: 8)
!587 = distinct !DILexicalBlock(scope: !581, file: !1, line: 127, column: 40)
!588 = !DILocation(line: 130, column: 15, scope: !586)
!589 = !DILocation(line: 130, column: 29, scope: !586)
!590 = !DILocation(line: 131, column: 6, scope: !586)
!591 = !DILocation(line: 131, column: 9, scope: !592)
!592 = !DILexicalBlockFile(scope: !586, file: !1, discriminator: 1)
!593 = !DILocation(line: 131, column: 16, scope: !592)
!594 = !DILocation(line: 132, column: 7, scope: !586)
!595 = !DILocation(line: 130, column: 8, scope: !596)
!596 = !DILexicalBlockFile(scope: !587, file: !1, discriminator: 1)
!597 = !DILocation(line: 133, column: 5, scope: !586)
!598 = !DILocation(line: 135, column: 4, scope: !587)
!599 = !DILocation(line: 135, column: 11, scope: !587)
!600 = !DILocation(line: 135, column: 20, scope: !587)
!601 = !DILocation(line: 136, column: 3, scope: !587)
!602 = !DILocation(line: 138, column: 4, scope: !603)
!603 = distinct !DILexicalBlock(scope: !581, file: !1, line: 136, column: 10)
!604 = !DILocalVariable(name: "ret_", scope: !605, file: !1, line: 138, type: !219)
!605 = distinct !DILexicalBlock(scope: !603, file: !1, line: 138, column: 4)
!606 = !DILocation(line: 138, column: 4, scope: !605)
!607 = !DILocation(line: 138, column: 4, scope: !608)
!608 = !DILexicalBlockFile(scope: !605, file: !1, discriminator: 1)
!609 = !DILocation(line: 138, column: 4, scope: !610)
!610 = !DILexicalBlockFile(scope: !611, file: !1, discriminator: 2)
!611 = distinct !DILexicalBlock(scope: !605, file: !1, line: 138, column: 4)
!612 = !DILocation(line: 138, column: 4, scope: !613)
!613 = !DILexicalBlockFile(scope: !605, file: !1, discriminator: 3)
!614 = !DILocation(line: 144, column: 24, scope: !603)
!615 = !DILocation(line: 144, column: 31, scope: !603)
!616 = !DILocation(line: 144, column: 22, scope: !603)
!617 = !DILocation(line: 144, column: 37, scope: !603)
!618 = !DILocation(line: 144, column: 4, scope: !603)
!619 = !DILocation(line: 144, column: 11, scope: !603)
!620 = !DILocation(line: 144, column: 20, scope: !603)
!621 = !DILocation(line: 149, column: 3, scope: !546)
!622 = !DILocation(line: 153, column: 40, scope: !491)
!623 = !DILocation(line: 153, column: 47, scope: !491)
!624 = !DILocation(line: 153, column: 16, scope: !491)
!625 = !DILocation(line: 153, column: 3, scope: !491)
!626 = !DILocation(line: 153, column: 10, scope: !491)
!627 = !DILocation(line: 153, column: 14, scope: !491)
!628 = !DILocation(line: 154, column: 3, scope: !491)
!629 = !DILocation(line: 154, column: 10, scope: !491)
!630 = !DILocation(line: 154, column: 19, scope: !491)
!631 = !DILocation(line: 159, column: 7, scope: !632)
!632 = distinct !DILexicalBlock(scope: !491, file: !1, line: 159, column: 7)
!633 = !DILocation(line: 159, column: 14, scope: !632)
!634 = !DILocation(line: 159, column: 18, scope: !632)
!635 = !DILocation(line: 159, column: 7, scope: !491)
!636 = !DILocation(line: 160, column: 6, scope: !637)
!637 = distinct !DILexicalBlock(scope: !632, file: !1, line: 159, column: 23)
!638 = !DILocation(line: 160, column: 13, scope: !637)
!639 = !DILocation(line: 160, column: 4, scope: !637)
!640 = !DILocation(line: 161, column: 13, scope: !641)
!641 = distinct !DILexicalBlock(scope: !637, file: !1, line: 161, column: 8)
!642 = !DILocation(line: 161, column: 20, scope: !641)
!643 = !DILocation(line: 161, column: 8, scope: !641)
!644 = !DILocation(line: 161, column: 24, scope: !641)
!645 = !DILocation(line: 161, column: 8, scope: !637)
!646 = !DILocation(line: 162, column: 5, scope: !641)
!647 = !DILocation(line: 164, column: 4, scope: !637)
!648 = !DILocation(line: 168, column: 29, scope: !491)
!649 = !DILocation(line: 168, column: 34, scope: !491)
!650 = !DILocation(line: 168, column: 32, scope: !491)
!651 = !DILocation(line: 169, column: 6, scope: !491)
!652 = !DILocation(line: 169, column: 5, scope: !491)
!653 = !DILocation(line: 169, column: 15, scope: !491)
!654 = !DILocation(line: 169, column: 13, scope: !491)
!655 = !DILocation(line: 169, column: 25, scope: !491)
!656 = !DILocation(line: 169, column: 32, scope: !491)
!657 = !DILocation(line: 168, column: 18, scope: !491)
!658 = !DILocation(line: 168, column: 3, scope: !491)
!659 = !DILocation(line: 168, column: 10, scope: !491)
!660 = !DILocation(line: 168, column: 16, scope: !491)
!661 = !DILocation(line: 171, column: 3, scope: !491)
!662 = !DILocation(line: 171, column: 10, scope: !491)
!663 = !DILocation(line: 171, column: 19, scope: !491)
!664 = !DILocation(line: 176, column: 3, scope: !491)
!665 = !DILocation(line: 177, column: 9, scope: !666)
!666 = distinct !DILexicalBlock(scope: !667, file: !1, line: 177, column: 8)
!667 = distinct !DILexicalBlock(scope: !491, file: !1, line: 176, column: 6)
!668 = !DILocation(line: 177, column: 8, scope: !666)
!669 = !DILocation(line: 177, column: 19, scope: !666)
!670 = !DILocation(line: 177, column: 16, scope: !666)
!671 = !DILocation(line: 177, column: 8, scope: !667)
!672 = !DILocation(line: 178, column: 5, scope: !666)
!673 = !DILocation(line: 180, column: 10, scope: !674)
!674 = distinct !DILexicalBlock(scope: !667, file: !1, line: 180, column: 8)
!675 = !DILocation(line: 180, column: 17, scope: !674)
!676 = !DILocation(line: 180, column: 27, scope: !674)
!677 = !DILocation(line: 180, column: 34, scope: !674)
!678 = !DILocation(line: 180, column: 38, scope: !674)
!679 = !DILocation(line: 180, column: 23, scope: !674)
!680 = !DILocation(line: 180, column: 44, scope: !674)
!681 = !DILocation(line: 181, column: 14, scope: !674)
!682 = !DILocation(line: 181, column: 21, scope: !674)
!683 = !DILocation(line: 181, column: 9, scope: !674)
!684 = !DILocation(line: 181, column: 6, scope: !674)
!685 = !DILocation(line: 180, column: 8, scope: !667)
!686 = !DILocation(line: 182, column: 5, scope: !674)
!687 = !DILocation(line: 184, column: 3, scope: !667)
!688 = !DILocation(line: 184, column: 14, scope: !689)
!689 = !DILexicalBlockFile(scope: !491, file: !1, discriminator: 1)
!690 = !DILocation(line: 184, column: 21, scope: !689)
!691 = !DILocation(line: 184, column: 12, scope: !689)
!692 = !DILocation(line: 184, column: 25, scope: !689)
!693 = !DILocation(line: 184, column: 3, scope: !689)
!694 = !DILocation(line: 188, column: 23, scope: !491)
!695 = !DILocation(line: 188, column: 30, scope: !491)
!696 = !DILocation(line: 188, column: 4, scope: !491)
!697 = !DILocation(line: 188, column: 11, scope: !491)
!698 = !DILocation(line: 188, column: 21, scope: !491)
!699 = !DILocation(line: 191, column: 3, scope: !491)
!700 = !DILocation(line: 191, column: 10, scope: !491)
!701 = !DILocation(line: 191, column: 16, scope: !491)
!702 = !DILocation(line: 193, column: 3, scope: !491)
!703 = !DILocation(line: 196, column: 3, scope: !491)
!704 = !DILocation(line: 69, column: 2, scope: !705)
!705 = !DILexicalBlockFile(scope: !200, file: !1, discriminator: 2)
!706 = !DILocation(line: 69, column: 2, scope: !707)
!707 = !DILexicalBlockFile(scope: !200, file: !1, discriminator: 3)
!708 = !DILocation(line: 202, column: 28, scope: !200)
!709 = !DILocation(line: 202, column: 33, scope: !200)
!710 = !DILocation(line: 202, column: 31, scope: !200)
!711 = !DILocation(line: 203, column: 5, scope: !200)
!712 = !DILocation(line: 203, column: 4, scope: !200)
!713 = !DILocation(line: 203, column: 14, scope: !200)
!714 = !DILocation(line: 203, column: 12, scope: !200)
!715 = !DILocation(line: 203, column: 24, scope: !200)
!716 = !DILocation(line: 203, column: 31, scope: !200)
!717 = !DILocation(line: 202, column: 17, scope: !200)
!718 = !DILocation(line: 202, column: 2, scope: !200)
!719 = !DILocation(line: 202, column: 9, scope: !200)
!720 = !DILocation(line: 202, column: 15, scope: !200)
!721 = !DILocation(line: 205, column: 9, scope: !200)
!722 = !DILocation(line: 205, column: 2, scope: !200)
!723 = !DILocation(line: 206, column: 1, scope: !200)
!724 = !DILocalVariable(name: "coder", arg: 1, scope: !195, file: !1, line: 210, type: !75)
!725 = !DILocation(line: 210, column: 31, scope: !195)
!726 = !DILocalVariable(name: "allocator", arg: 2, scope: !195, file: !1, line: 210, type: !86)
!727 = !DILocation(line: 210, column: 54, scope: !195)
!728 = !DILocation(line: 212, column: 17, scope: !195)
!729 = !DILocation(line: 212, column: 24, scope: !195)
!730 = !DILocation(line: 212, column: 31, scope: !195)
!731 = !DILocation(line: 212, column: 2, scope: !195)
!732 = !DILocation(line: 213, column: 12, scope: !195)
!733 = !DILocation(line: 213, column: 19, scope: !195)
!734 = !DILocation(line: 213, column: 2, scope: !195)
!735 = !DILocation(line: 214, column: 2, scope: !195)
!736 = !DILocalVariable(name: "coder", arg: 1, scope: !196, file: !1, line: 219, type: !75)
!737 = !DILocation(line: 219, column: 37, scope: !196)
!738 = !DILocalVariable(name: "memusage", arg: 2, scope: !196, file: !1, line: 219, type: !126)
!739 = !DILocation(line: 219, column: 54, scope: !196)
!740 = !DILocalVariable(name: "old_memlimit", arg: 3, scope: !196, file: !1, line: 220, type: !126)
!741 = !DILocation(line: 220, column: 13, scope: !196)
!742 = !DILocalVariable(name: "new_memlimit", arg: 4, scope: !196, file: !1, line: 220, type: !23)
!743 = !DILocation(line: 220, column: 36, scope: !196)
!744 = !DILocation(line: 222, column: 37, scope: !196)
!745 = !DILocation(line: 222, column: 44, scope: !196)
!746 = !DILocation(line: 222, column: 14, scope: !196)
!747 = !DILocation(line: 222, column: 3, scope: !196)
!748 = !DILocation(line: 222, column: 12, scope: !196)
!749 = !DILocation(line: 223, column: 18, scope: !196)
!750 = !DILocation(line: 223, column: 25, scope: !196)
!751 = !DILocation(line: 223, column: 3, scope: !196)
!752 = !DILocation(line: 223, column: 16, scope: !196)
!753 = !DILocation(line: 225, column: 6, scope: !754)
!754 = distinct !DILexicalBlock(scope: !196, file: !1, line: 225, column: 6)
!755 = !DILocation(line: 225, column: 19, scope: !754)
!756 = !DILocation(line: 225, column: 6, scope: !196)
!757 = !DILocation(line: 226, column: 7, scope: !758)
!758 = distinct !DILexicalBlock(scope: !759, file: !1, line: 226, column: 7)
!759 = distinct !DILexicalBlock(scope: !754, file: !1, line: 225, column: 25)
!760 = !DILocation(line: 226, column: 23, scope: !758)
!761 = !DILocation(line: 226, column: 22, scope: !758)
!762 = !DILocation(line: 226, column: 20, scope: !758)
!763 = !DILocation(line: 226, column: 7, scope: !759)
!764 = !DILocation(line: 227, column: 4, scope: !758)
!765 = !DILocation(line: 229, column: 21, scope: !759)
!766 = !DILocation(line: 229, column: 3, scope: !759)
!767 = !DILocation(line: 229, column: 10, scope: !759)
!768 = !DILocation(line: 229, column: 19, scope: !759)
!769 = !DILocation(line: 230, column: 2, scope: !759)
!770 = !DILocation(line: 232, column: 2, scope: !196)
!771 = !DILocation(line: 233, column: 1, scope: !196)
