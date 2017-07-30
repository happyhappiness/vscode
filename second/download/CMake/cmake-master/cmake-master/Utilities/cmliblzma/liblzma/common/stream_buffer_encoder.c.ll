; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/stream_buffer_encoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_filter = type { i64, i8* }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_stream_flags = type { i32, i64, i32, i32, i32, i32, i32, i8, i8, i8, i8, i8, i8, i8, i8, i32, i32 }
%struct.lzma_block = type { i32, i32, i32, i64, i64, %struct.lzma_filter*, [64 x i8], i8*, i8*, i8*, i32, i32, i64, i64, i64, i64, i64, i64, i32, i32, i32, i32, i8, i8, i8, i8, i8, i8, i8, i8 }
%struct.lzma_index_s = type opaque

; Function Attrs: nounwind uwtable
define i64 @lzma_stream_buffer_bound(i64 %uncompressed_size) #0 !dbg !32 {
entry:
  %retval = alloca i64, align 8
  %uncompressed_size.addr = alloca i64, align 8
  %block_bound = alloca i64, align 8
  store i64 %uncompressed_size, i64* %uncompressed_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %uncompressed_size.addr, metadata !77, metadata !78), !dbg !79
  call void @llvm.dbg.declare(metadata i64* %block_bound, metadata !80, metadata !78), !dbg !82
  %0 = load i64, i64* %uncompressed_size.addr, align 8, !dbg !83
  %call = call i64 @lzma_block_buffer_bound(i64 %0) #6, !dbg !84
  store i64 %call, i64* %block_bound, align 8, !dbg !82
  %1 = load i64, i64* %block_bound, align 8, !dbg !85
  %cmp = icmp eq i64 %1, 0, !dbg !87
  br i1 %cmp, label %if.then, label %if.end, !dbg !88

if.then:                                          ; preds = %entry
  store i64 0, i64* %retval, align 8, !dbg !89
  br label %return, !dbg !89

if.end:                                           ; preds = %entry
  %2 = load i64, i64* %block_bound, align 8, !dbg !90
  %sub = sub i64 9223372036854775807, %2, !dbg !92
  %cmp1 = icmp ult i64 %sub, 48, !dbg !93
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !94

if.then2:                                         ; preds = %if.end
  store i64 0, i64* %retval, align 8, !dbg !95
  br label %return, !dbg !95

if.end3:                                          ; preds = %if.end
  %3 = load i64, i64* %block_bound, align 8, !dbg !96
  %add = add i64 %3, 48, !dbg !97
  store i64 %add, i64* %retval, align 8, !dbg !98
  br label %return, !dbg !98

return:                                           ; preds = %if.end3, %if.then2, %if.then
  %4 = load i64, i64* %retval, align 8, !dbg !99
  ret i64 %4, !dbg !99
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare i64 @lzma_block_buffer_bound(i64) #2

; Function Attrs: nounwind uwtable
define i32 @lzma_stream_buffer_encode(%struct.lzma_filter* %filters, i32 %check, %struct.lzma_allocator* %allocator, i8* %in, i64 %in_size, i8* %out, i64* %out_pos_ptr, i64 %out_size) #0 !dbg !39 {
entry:
  %retval = alloca i32, align 4
  %filters.addr = alloca %struct.lzma_filter*, align 8
  %check.addr = alloca i32, align 4
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %in.addr = alloca i8*, align 8
  %in_size.addr = alloca i64, align 8
  %out.addr = alloca i8*, align 8
  %out_pos_ptr.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  %stream_flags = alloca %struct.lzma_stream_flags, align 8
  %block = alloca %struct.lzma_block, align 8
  %out_pos = alloca i64, align 8
  %ret_ = alloca i32, align 4
  %ret = alloca i32, align 4
  %i = alloca %struct.lzma_index_s*, align 8
  store %struct.lzma_filter* %filters, %struct.lzma_filter** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %filters.addr, metadata !100, metadata !78), !dbg !101
  store i32 %check, i32* %check.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %check.addr, metadata !102, metadata !78), !dbg !103
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !104, metadata !78), !dbg !105
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !106, metadata !78), !dbg !107
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !108, metadata !78), !dbg !109
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !110, metadata !78), !dbg !111
  store i64* %out_pos_ptr, i64** %out_pos_ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos_ptr.addr, metadata !112, metadata !78), !dbg !113
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !114, metadata !78), !dbg !115
  call void @llvm.dbg.declare(metadata %struct.lzma_stream_flags* %stream_flags, metadata !116, metadata !78), !dbg !141
  %0 = bitcast %struct.lzma_stream_flags* %stream_flags to i8*, !dbg !141
  call void @llvm.memset.p0i8.i64(i8* %0, i8 0, i64 56, i32 8, i1 false), !dbg !141
  call void @llvm.dbg.declare(metadata %struct.lzma_block* %block, metadata !142, metadata !78), !dbg !180
  %1 = bitcast %struct.lzma_block* %block to i8*, !dbg !180
  call void @llvm.memset.p0i8.i64(i8* %1, i8 0, i64 208, i32 8, i1 false), !dbg !180
  call void @llvm.dbg.declare(metadata i64* %out_pos, metadata !181, metadata !78), !dbg !182
  %2 = load %struct.lzma_filter*, %struct.lzma_filter** %filters.addr, align 8, !dbg !183
  %cmp = icmp eq %struct.lzma_filter* %2, null, !dbg !185
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !186

lor.lhs.false:                                    ; preds = %entry
  %3 = load i32, i32* %check.addr, align 4, !dbg !187
  %cmp1 = icmp ugt i32 %3, 15, !dbg !189
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !190

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %4 = load i8*, i8** %in.addr, align 8, !dbg !191
  %cmp3 = icmp eq i8* %4, null, !dbg !192
  br i1 %cmp3, label %land.lhs.true, label %lor.lhs.false5, !dbg !193

land.lhs.true:                                    ; preds = %lor.lhs.false2
  %5 = load i64, i64* %in_size.addr, align 8, !dbg !194
  %cmp4 = icmp ne i64 %5, 0, !dbg !196
  br i1 %cmp4, label %if.then, label %lor.lhs.false5, !dbg !197

lor.lhs.false5:                                   ; preds = %land.lhs.true, %lor.lhs.false2
  %6 = load i8*, i8** %out.addr, align 8, !dbg !198
  %cmp6 = icmp eq i8* %6, null, !dbg !200
  br i1 %cmp6, label %if.then, label %lor.lhs.false7, !dbg !201

lor.lhs.false7:                                   ; preds = %lor.lhs.false5
  %7 = load i64*, i64** %out_pos_ptr.addr, align 8, !dbg !202
  %cmp8 = icmp eq i64* %7, null, !dbg !203
  br i1 %cmp8, label %if.then, label %lor.lhs.false9, !dbg !204

lor.lhs.false9:                                   ; preds = %lor.lhs.false7
  %8 = load i64*, i64** %out_pos_ptr.addr, align 8, !dbg !205
  %9 = load i64, i64* %8, align 8, !dbg !206
  %10 = load i64, i64* %out_size.addr, align 8, !dbg !207
  %cmp10 = icmp ugt i64 %9, %10, !dbg !208
  br i1 %cmp10, label %if.then, label %if.end, !dbg !209

if.then:                                          ; preds = %lor.lhs.false9, %lor.lhs.false7, %lor.lhs.false5, %land.lhs.true, %lor.lhs.false, %entry
  store i32 11, i32* %retval, align 4, !dbg !211
  br label %return, !dbg !211

if.end:                                           ; preds = %lor.lhs.false9
  %11 = load i32, i32* %check.addr, align 4, !dbg !212
  %call = call zeroext i8 @lzma_check_is_supported(i32 %11) #1, !dbg !214
  %tobool = icmp ne i8 %call, 0, !dbg !214
  br i1 %tobool, label %if.end12, label %if.then11, !dbg !215

if.then11:                                        ; preds = %if.end
  store i32 3, i32* %retval, align 4, !dbg !216
  br label %return, !dbg !216

if.end12:                                         ; preds = %if.end
  %12 = load i64*, i64** %out_pos_ptr.addr, align 8, !dbg !217
  %13 = load i64, i64* %12, align 8, !dbg !218
  store i64 %13, i64* %out_pos, align 8, !dbg !219
  %14 = load i64, i64* %out_size.addr, align 8, !dbg !220
  %15 = load i64, i64* %out_pos, align 8, !dbg !222
  %sub = sub i64 %14, %15, !dbg !223
  %cmp13 = icmp ule i64 %sub, 24, !dbg !224
  br i1 %cmp13, label %if.then14, label %if.end15, !dbg !225

if.then14:                                        ; preds = %if.end12
  store i32 10, i32* %retval, align 4, !dbg !226
  br label %return, !dbg !226

if.end15:                                         ; preds = %if.end12
  %16 = load i64, i64* %out_size.addr, align 8, !dbg !227
  %sub16 = sub i64 %16, 12, !dbg !227
  store i64 %sub16, i64* %out_size.addr, align 8, !dbg !227
  %17 = load i32, i32* %check.addr, align 4, !dbg !228
  %check17 = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 2, !dbg !229
  store i32 %17, i32* %check17, align 8, !dbg !230
  %18 = load i8*, i8** %out.addr, align 8, !dbg !231
  %19 = load i64, i64* %out_pos, align 8, !dbg !233
  %add.ptr = getelementptr inbounds i8, i8* %18, i64 %19, !dbg !234
  %call18 = call i32 @lzma_stream_header_encode(%struct.lzma_stream_flags* %stream_flags, i8* %add.ptr) #6, !dbg !235
  %cmp19 = icmp ne i32 %call18, 0, !dbg !236
  br i1 %cmp19, label %if.then20, label %if.end21, !dbg !237

if.then20:                                        ; preds = %if.end15
  store i32 11, i32* %retval, align 4, !dbg !238
  br label %return, !dbg !238

if.end21:                                         ; preds = %if.end15
  %20 = load i64, i64* %out_pos, align 8, !dbg !239
  %add = add i64 %20, 12, !dbg !239
  store i64 %add, i64* %out_pos, align 8, !dbg !239
  %21 = load i32, i32* %check.addr, align 4, !dbg !240
  %check22 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %block, i32 0, i32 2, !dbg !241
  store i32 %21, i32* %check22, align 8, !dbg !242
  %22 = load %struct.lzma_filter*, %struct.lzma_filter** %filters.addr, align 8, !dbg !243
  %filters23 = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %block, i32 0, i32 5, !dbg !244
  store %struct.lzma_filter* %22, %struct.lzma_filter** %filters23, align 8, !dbg !245
  %23 = load i64, i64* %in_size.addr, align 8, !dbg !246
  %cmp24 = icmp ugt i64 %23, 0, !dbg !248
  br i1 %cmp24, label %if.then25, label %if.end30, !dbg !249

if.then25:                                        ; preds = %if.end21
  br label %do.body, !dbg !250

do.body:                                          ; preds = %if.then25
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !251, metadata !78), !dbg !254
  %24 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !255
  %25 = load i8*, i8** %in.addr, align 8, !dbg !255
  %26 = load i64, i64* %in_size.addr, align 8, !dbg !255
  %27 = load i8*, i8** %out.addr, align 8, !dbg !255
  %28 = load i64, i64* %out_size.addr, align 8, !dbg !255
  %call26 = call i32 @lzma_block_buffer_encode(%struct.lzma_block* %block, %struct.lzma_allocator* %24, i8* %25, i64 %26, i8* %27, i64* %out_pos, i64 %28) #6, !dbg !255
  store i32 %call26, i32* %ret_, align 4, !dbg !255
  %29 = load i32, i32* %ret_, align 4, !dbg !255
  %cmp27 = icmp ne i32 %29, 0, !dbg !255
  br i1 %cmp27, label %if.then28, label %if.end29, !dbg !255

if.then28:                                        ; preds = %do.body
  %30 = load i32, i32* %ret_, align 4, !dbg !257
  store i32 %30, i32* %retval, align 4, !dbg !257
  br label %return, !dbg !257

if.end29:                                         ; preds = %do.body
  br label %do.end, !dbg !260

do.end:                                           ; preds = %if.end29
  br label %if.end30, !dbg !262

if.end30:                                         ; preds = %do.end, %if.end21
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !264, metadata !78), !dbg !266
  call void @llvm.dbg.declare(metadata %struct.lzma_index_s** %i, metadata !267, metadata !78), !dbg !272
  %31 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !273
  %call31 = call %struct.lzma_index_s* @lzma_index_init(%struct.lzma_allocator* %31) #6, !dbg !274
  store %struct.lzma_index_s* %call31, %struct.lzma_index_s** %i, align 8, !dbg !272
  %32 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i, align 8, !dbg !275
  %cmp32 = icmp eq %struct.lzma_index_s* %32, null, !dbg !277
  br i1 %cmp32, label %if.then33, label %if.end34, !dbg !278

if.then33:                                        ; preds = %if.end30
  store i32 5, i32* %retval, align 4, !dbg !279
  br label %return, !dbg !279

if.end34:                                         ; preds = %if.end30
  store i32 0, i32* %ret, align 4, !dbg !280
  %33 = load i64, i64* %in_size.addr, align 8, !dbg !281
  %cmp35 = icmp ugt i64 %33, 0, !dbg !283
  br i1 %cmp35, label %if.then36, label %if.end39, !dbg !284

if.then36:                                        ; preds = %if.end34
  %34 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i, align 8, !dbg !285
  %35 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !286
  %call37 = call i64 @lzma_block_unpadded_size(%struct.lzma_block* %block) #7, !dbg !287
  %uncompressed_size = getelementptr inbounds %struct.lzma_block, %struct.lzma_block* %block, i32 0, i32 4, !dbg !288
  %36 = load i64, i64* %uncompressed_size, align 8, !dbg !288
  %call38 = call i32 @lzma_index_append(%struct.lzma_index_s* %34, %struct.lzma_allocator* %35, i64 %call37, i64 %36) #6, !dbg !289
  store i32 %call38, i32* %ret, align 4, !dbg !290
  br label %if.end39, !dbg !291

if.end39:                                         ; preds = %if.then36, %if.end34
  %37 = load i32, i32* %ret, align 4, !dbg !292
  %cmp40 = icmp eq i32 %37, 0, !dbg !294
  br i1 %cmp40, label %if.then41, label %if.end44, !dbg !295

if.then41:                                        ; preds = %if.end39
  %38 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i, align 8, !dbg !296
  %39 = load i8*, i8** %out.addr, align 8, !dbg !298
  %40 = load i64, i64* %out_size.addr, align 8, !dbg !299
  %call42 = call i32 @lzma_index_buffer_encode(%struct.lzma_index_s* %38, i8* %39, i64* %out_pos, i64 %40) #6, !dbg !300
  store i32 %call42, i32* %ret, align 4, !dbg !301
  %41 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i, align 8, !dbg !302
  %call43 = call i64 @lzma_index_size(%struct.lzma_index_s* %41) #7, !dbg !303
  %backward_size = getelementptr inbounds %struct.lzma_stream_flags, %struct.lzma_stream_flags* %stream_flags, i32 0, i32 1, !dbg !304
  store i64 %call43, i64* %backward_size, align 8, !dbg !305
  br label %if.end44, !dbg !306

if.end44:                                         ; preds = %if.then41, %if.end39
  %42 = load %struct.lzma_index_s*, %struct.lzma_index_s** %i, align 8, !dbg !307
  %43 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !308
  call void @lzma_index_end(%struct.lzma_index_s* %42, %struct.lzma_allocator* %43) #6, !dbg !309
  %44 = load i32, i32* %ret, align 4, !dbg !310
  %cmp45 = icmp ne i32 %44, 0, !dbg !312
  br i1 %cmp45, label %if.then46, label %if.end47, !dbg !313

if.then46:                                        ; preds = %if.end44
  %45 = load i32, i32* %ret, align 4, !dbg !314
  store i32 %45, i32* %retval, align 4, !dbg !315
  br label %return, !dbg !315

if.end47:                                         ; preds = %if.end44
  %46 = load i8*, i8** %out.addr, align 8, !dbg !316
  %47 = load i64, i64* %out_pos, align 8, !dbg !318
  %add.ptr48 = getelementptr inbounds i8, i8* %46, i64 %47, !dbg !319
  %call49 = call i32 @lzma_stream_footer_encode(%struct.lzma_stream_flags* %stream_flags, i8* %add.ptr48) #6, !dbg !320
  %cmp50 = icmp ne i32 %call49, 0, !dbg !321
  br i1 %cmp50, label %if.then51, label %if.end52, !dbg !322

if.then51:                                        ; preds = %if.end47
  store i32 11, i32* %retval, align 4, !dbg !323
  br label %return, !dbg !323

if.end52:                                         ; preds = %if.end47
  %48 = load i64, i64* %out_pos, align 8, !dbg !324
  %add53 = add i64 %48, 12, !dbg !324
  store i64 %add53, i64* %out_pos, align 8, !dbg !324
  %49 = load i64, i64* %out_pos, align 8, !dbg !325
  %50 = load i64*, i64** %out_pos_ptr.addr, align 8, !dbg !326
  store i64 %49, i64* %50, align 8, !dbg !327
  store i32 0, i32* %retval, align 4, !dbg !328
  br label %return, !dbg !328

return:                                           ; preds = %if.end52, %if.then51, %if.then46, %if.then33, %if.then28, %if.then20, %if.then14, %if.then11, %if.then
  %51 = load i32, i32* %retval, align 4, !dbg !329
  ret i32 %51, !dbg !329
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #3

; Function Attrs: nounwind readnone
declare zeroext i8 @lzma_check_is_supported(i32) #4

; Function Attrs: nounwind
declare i32 @lzma_stream_header_encode(%struct.lzma_stream_flags*, i8*) #2

; Function Attrs: nounwind
declare i32 @lzma_block_buffer_encode(%struct.lzma_block*, %struct.lzma_allocator*, i8*, i64, i8*, i64*, i64) #2

; Function Attrs: nounwind
declare %struct.lzma_index_s* @lzma_index_init(%struct.lzma_allocator*) #2

; Function Attrs: nounwind
declare i32 @lzma_index_append(%struct.lzma_index_s*, %struct.lzma_allocator*, i64, i64) #2

; Function Attrs: nounwind readonly
declare i64 @lzma_block_unpadded_size(%struct.lzma_block*) #5

; Function Attrs: nounwind
declare i32 @lzma_index_buffer_encode(%struct.lzma_index_s*, i8*, i64*, i64) #2

; Function Attrs: nounwind readonly
declare i64 @lzma_index_size(%struct.lzma_index_s*) #5

; Function Attrs: nounwind
declare void @lzma_index_end(%struct.lzma_index_s*, %struct.lzma_allocator*) #2

; Function Attrs: nounwind
declare i32 @lzma_stream_footer_encode(%struct.lzma_stream_flags*, i8*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind }
attributes #4 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind }
attributes #7 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!74, !75}
!llvm.ident = !{!76}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !28, subprograms: !31)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/stream_buffer_encoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !25}
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
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !19, line: 27, size: 32, align: 32, elements: !20)
!19 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!20 = !{!21, !22, !23, !24}
!21 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!22 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!23 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!24 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!25 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 44, size: 32, align: 32, elements: !26)
!26 = !{!27}
!27 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!28 = !{!29, !30}
!29 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!30 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!31 = !{!32, !39}
!32 = distinct !DISubprogram(name: "lzma_stream_buffer_bound", scope: !1, file: !1, line: 26, type: !33, isLocal: false, isDefinition: true, scopeLine: 27, flags: DIFlagPrototyped, isOptimized: false, variables: !38)
!33 = !DISubroutineType(types: !34)
!34 = !{!35, !35}
!35 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !36, line: 62, baseType: !37)
!36 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!37 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!38 = !{}
!39 = distinct !DISubprogram(name: "lzma_stream_buffer_encode", scope: !1, file: !1, line: 44, type: !40, isLocal: false, isDefinition: true, scopeLine: 47, flags: DIFlagPrototyped, isOptimized: false, variables: !38)
!40 = !DISubroutineType(types: !41)
!41 = !{!42, !43, !54, !55, !68, !35, !72, !73, !35}
!42 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!44 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !45, line: 65, baseType: !46)
!45 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!46 = !DICompositeType(tag: DW_TAG_structure_type, file: !45, line: 43, size: 128, align: 64, elements: !47)
!47 = !{!48, !53}
!48 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !46, file: !45, line: 54, baseType: !49, size: 64, align: 64)
!49 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !50, line: 63, baseType: !51)
!50 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!51 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !52, line: 55, baseType: !37)
!52 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!53 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !46, file: !45, line: 63, baseType: !29, size: 64, align: 64, offset: 64)
!54 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !19, line: 55, baseType: !18)
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!56 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !57)
!57 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !58)
!58 = !{!59, !63, !67}
!59 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !57, file: !4, line: 376, baseType: !60, size: 64, align: 64)
!60 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !61, size: 64, align: 64)
!61 = !DISubroutineType(types: !62)
!62 = !{!29, !29, !35, !35}
!63 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !57, file: !4, line: 390, baseType: !64, size: 64, align: 64, offset: 64)
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !65, size: 64, align: 64)
!65 = !DISubroutineType(types: !66)
!66 = !{null, !29, !29}
!67 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !57, file: !4, line: 401, baseType: !29, size: 64, align: 64, offset: 128)
!68 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !69, size: 64, align: 64)
!69 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !70)
!70 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !52, line: 48, baseType: !71)
!71 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!72 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !35, size: 64, align: 64)
!74 = !{i32 2, !"Dwarf Version", i32 4}
!75 = !{i32 2, !"Debug Info Version", i32 3}
!76 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!77 = !DILocalVariable(name: "uncompressed_size", arg: 1, scope: !32, file: !1, line: 26, type: !35)
!78 = !DIExpression()
!79 = !DILocation(line: 26, column: 33, scope: !32)
!80 = !DILocalVariable(name: "block_bound", scope: !32, file: !1, line: 29, type: !81)
!81 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !35)
!82 = !DILocation(line: 29, column: 15, scope: !32)
!83 = !DILocation(line: 29, column: 53, scope: !32)
!84 = !DILocation(line: 29, column: 29, scope: !32)
!85 = !DILocation(line: 30, column: 6, scope: !86)
!86 = distinct !DILexicalBlock(scope: !32, file: !1, line: 30, column: 6)
!87 = !DILocation(line: 30, column: 18, scope: !86)
!88 = !DILocation(line: 30, column: 6, scope: !32)
!89 = !DILocation(line: 31, column: 3, scope: !86)
!90 = !DILocation(line: 36, column: 39, scope: !91)
!91 = distinct !DILexicalBlock(scope: !32, file: !1, line: 36, column: 6)
!92 = !DILocation(line: 36, column: 37, scope: !91)
!93 = !DILocation(line: 36, column: 51, scope: !91)
!94 = !DILocation(line: 36, column: 6, scope: !32)
!95 = !DILocation(line: 37, column: 3, scope: !91)
!96 = !DILocation(line: 39, column: 9, scope: !32)
!97 = !DILocation(line: 39, column: 21, scope: !32)
!98 = !DILocation(line: 39, column: 2, scope: !32)
!99 = !DILocation(line: 40, column: 1, scope: !32)
!100 = !DILocalVariable(name: "filters", arg: 1, scope: !39, file: !1, line: 44, type: !43)
!101 = !DILocation(line: 44, column: 40, scope: !39)
!102 = !DILocalVariable(name: "check", arg: 2, scope: !39, file: !1, line: 44, type: !54)
!103 = !DILocation(line: 44, column: 60, scope: !39)
!104 = !DILocalVariable(name: "allocator", arg: 3, scope: !39, file: !1, line: 45, type: !55)
!105 = !DILocation(line: 45, column: 19, scope: !39)
!106 = !DILocalVariable(name: "in", arg: 4, scope: !39, file: !1, line: 45, type: !68)
!107 = !DILocation(line: 45, column: 45, scope: !39)
!108 = !DILocalVariable(name: "in_size", arg: 5, scope: !39, file: !1, line: 45, type: !35)
!109 = !DILocation(line: 45, column: 56, scope: !39)
!110 = !DILocalVariable(name: "out", arg: 6, scope: !39, file: !1, line: 46, type: !72)
!111 = !DILocation(line: 46, column: 12, scope: !39)
!112 = !DILocalVariable(name: "out_pos_ptr", arg: 7, scope: !39, file: !1, line: 46, type: !73)
!113 = !DILocation(line: 46, column: 25, scope: !39)
!114 = !DILocalVariable(name: "out_size", arg: 8, scope: !39, file: !1, line: 46, type: !35)
!115 = !DILocation(line: 46, column: 45, scope: !39)
!116 = !DILocalVariable(name: "stream_flags", scope: !39, file: !1, line: 48, type: !117)
!117 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_stream_flags", file: !118, line: 105, baseType: !119)
!118 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/stream_flags.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!119 = !DICompositeType(tag: DW_TAG_structure_type, file: !118, line: 33, size: 448, align: 64, elements: !120)
!120 = !{!121, !123, !124, !125, !127, !128, !129, !130, !132, !133, !134, !135, !136, !137, !138, !139, !140}
!121 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !119, file: !118, line: 51, baseType: !122, size: 32, align: 32)
!122 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !52, line: 51, baseType: !30)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "backward_size", scope: !119, file: !118, line: 69, baseType: !49, size: 64, align: 64, offset: 64)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "check", scope: !119, file: !118, line: 79, baseType: !54, size: 32, align: 32, offset: 128)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !119, file: !118, line: 90, baseType: !126, size: 32, align: 32, offset: 160)
!126 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !25)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !119, file: !118, line: 91, baseType: !126, size: 32, align: 32, offset: 192)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !119, file: !118, line: 92, baseType: !126, size: 32, align: 32, offset: 224)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !119, file: !118, line: 93, baseType: !126, size: 32, align: 32, offset: 256)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool1", scope: !119, file: !118, line: 94, baseType: !131, size: 8, align: 8, offset: 288)
!131 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_bool", file: !4, line: 29, baseType: !71)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool2", scope: !119, file: !118, line: 95, baseType: !131, size: 8, align: 8, offset: 296)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool3", scope: !119, file: !118, line: 96, baseType: !131, size: 8, align: 8, offset: 304)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool4", scope: !119, file: !118, line: 97, baseType: !131, size: 8, align: 8, offset: 312)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool5", scope: !119, file: !118, line: 98, baseType: !131, size: 8, align: 8, offset: 320)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool6", scope: !119, file: !118, line: 99, baseType: !131, size: 8, align: 8, offset: 328)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool7", scope: !119, file: !118, line: 100, baseType: !131, size: 8, align: 8, offset: 336)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool8", scope: !119, file: !118, line: 101, baseType: !131, size: 8, align: 8, offset: 344)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !119, file: !118, line: 102, baseType: !122, size: 32, align: 32, offset: 352)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !119, file: !118, line: 103, baseType: !122, size: 32, align: 32, offset: 384)
!141 = !DILocation(line: 48, column: 20, scope: !39)
!142 = !DILocalVariable(name: "block", scope: !39, file: !1, line: 49, type: !143)
!143 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_block", file: !144, line: 245, baseType: !145)
!144 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/block.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!145 = !DICompositeType(tag: DW_TAG_structure_type, file: !144, line: 30, size: 1664, align: 64, elements: !146)
!146 = !{!147, !148, !149, !150, !151, !152, !153, !157, !158, !159, !160, !161, !162, !163, !164, !165, !166, !167, !168, !169, !170, !171, !172, !173, !174, !175, !176, !177, !178, !179}
!147 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !145, file: !144, line: 47, baseType: !122, size: 32, align: 32)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "header_size", scope: !145, file: !144, line: 67, baseType: !122, size: 32, align: 32, offset: 32)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "check", scope: !145, file: !144, line: 88, baseType: !54, size: 32, align: 32, offset: 64)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "compressed_size", scope: !145, file: !144, line: 143, baseType: !49, size: 64, align: 64, offset: 128)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_size", scope: !145, file: !144, line: 167, baseType: !49, size: 64, align: 64, offset: 192)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "filters", scope: !145, file: !144, line: 195, baseType: !43, size: 64, align: 64, offset: 256)
!153 = !DIDerivedType(tag: DW_TAG_member, name: "raw_check", scope: !145, file: !144, line: 212, baseType: !154, size: 512, align: 8, offset: 320)
!154 = !DICompositeType(tag: DW_TAG_array_type, baseType: !70, size: 512, align: 8, elements: !155)
!155 = !{!156}
!156 = !DISubrange(count: 64)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !145, file: !144, line: 221, baseType: !29, size: 64, align: 64, offset: 832)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !145, file: !144, line: 222, baseType: !29, size: 64, align: 64, offset: 896)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !145, file: !144, line: 223, baseType: !29, size: 64, align: 64, offset: 960)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !145, file: !144, line: 224, baseType: !122, size: 32, align: 32, offset: 1024)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !145, file: !144, line: 225, baseType: !122, size: 32, align: 32, offset: 1056)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !145, file: !144, line: 226, baseType: !49, size: 64, align: 64, offset: 1088)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !145, file: !144, line: 227, baseType: !49, size: 64, align: 64, offset: 1152)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int5", scope: !145, file: !144, line: 228, baseType: !49, size: 64, align: 64, offset: 1216)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int6", scope: !145, file: !144, line: 229, baseType: !49, size: 64, align: 64, offset: 1280)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int7", scope: !145, file: !144, line: 230, baseType: !49, size: 64, align: 64, offset: 1344)
!167 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int8", scope: !145, file: !144, line: 231, baseType: !49, size: 64, align: 64, offset: 1408)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !145, file: !144, line: 232, baseType: !126, size: 32, align: 32, offset: 1472)
!169 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !145, file: !144, line: 233, baseType: !126, size: 32, align: 32, offset: 1504)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !145, file: !144, line: 234, baseType: !126, size: 32, align: 32, offset: 1536)
!171 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !145, file: !144, line: 235, baseType: !126, size: 32, align: 32, offset: 1568)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool1", scope: !145, file: !144, line: 236, baseType: !131, size: 8, align: 8, offset: 1600)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool2", scope: !145, file: !144, line: 237, baseType: !131, size: 8, align: 8, offset: 1608)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool3", scope: !145, file: !144, line: 238, baseType: !131, size: 8, align: 8, offset: 1616)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool4", scope: !145, file: !144, line: 239, baseType: !131, size: 8, align: 8, offset: 1624)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool5", scope: !145, file: !144, line: 240, baseType: !131, size: 8, align: 8, offset: 1632)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool6", scope: !145, file: !144, line: 241, baseType: !131, size: 8, align: 8, offset: 1640)
!178 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool7", scope: !145, file: !144, line: 242, baseType: !131, size: 8, align: 8, offset: 1648)
!179 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_bool8", scope: !145, file: !144, line: 243, baseType: !131, size: 8, align: 8, offset: 1656)
!180 = !DILocation(line: 49, column: 13, scope: !39)
!181 = !DILocalVariable(name: "out_pos", scope: !39, file: !1, line: 50, type: !35)
!182 = !DILocation(line: 50, column: 9, scope: !39)
!183 = !DILocation(line: 53, column: 6, scope: !184)
!184 = distinct !DILexicalBlock(scope: !39, file: !1, line: 53, column: 6)
!185 = !DILocation(line: 53, column: 14, scope: !184)
!186 = !DILocation(line: 53, column: 22, scope: !184)
!187 = !DILocation(line: 53, column: 40, scope: !188)
!188 = !DILexicalBlockFile(scope: !184, file: !1, discriminator: 1)
!189 = !DILocation(line: 53, column: 47, scope: !188)
!190 = !DILocation(line: 54, column: 4, scope: !184)
!191 = !DILocation(line: 54, column: 8, scope: !188)
!192 = !DILocation(line: 54, column: 11, scope: !188)
!193 = !DILocation(line: 54, column: 19, scope: !188)
!194 = !DILocation(line: 54, column: 22, scope: !195)
!195 = !DILexicalBlockFile(scope: !184, file: !1, discriminator: 2)
!196 = !DILocation(line: 54, column: 30, scope: !195)
!197 = !DILocation(line: 54, column: 36, scope: !195)
!198 = !DILocation(line: 54, column: 39, scope: !199)
!199 = !DILexicalBlockFile(scope: !184, file: !1, discriminator: 3)
!200 = !DILocation(line: 54, column: 43, scope: !199)
!201 = !DILocation(line: 55, column: 4, scope: !184)
!202 = !DILocation(line: 55, column: 7, scope: !188)
!203 = !DILocation(line: 55, column: 19, scope: !188)
!204 = !DILocation(line: 55, column: 27, scope: !188)
!205 = !DILocation(line: 55, column: 31, scope: !195)
!206 = !DILocation(line: 55, column: 30, scope: !195)
!207 = !DILocation(line: 55, column: 45, scope: !195)
!208 = !DILocation(line: 55, column: 43, scope: !195)
!209 = !DILocation(line: 53, column: 6, scope: !210)
!210 = !DILexicalBlockFile(scope: !39, file: !1, discriminator: 2)
!211 = !DILocation(line: 56, column: 3, scope: !184)
!212 = !DILocation(line: 58, column: 31, scope: !213)
!213 = distinct !DILexicalBlock(scope: !39, file: !1, line: 58, column: 6)
!214 = !DILocation(line: 58, column: 7, scope: !213)
!215 = !DILocation(line: 58, column: 6, scope: !39)
!216 = !DILocation(line: 59, column: 3, scope: !213)
!217 = !DILocation(line: 68, column: 13, scope: !39)
!218 = !DILocation(line: 68, column: 12, scope: !39)
!219 = !DILocation(line: 68, column: 10, scope: !39)
!220 = !DILocation(line: 72, column: 6, scope: !221)
!221 = distinct !DILexicalBlock(scope: !39, file: !1, line: 72, column: 6)
!222 = !DILocation(line: 72, column: 17, scope: !221)
!223 = !DILocation(line: 72, column: 15, scope: !221)
!224 = !DILocation(line: 72, column: 25, scope: !221)
!225 = !DILocation(line: 72, column: 6, scope: !39)
!226 = !DILocation(line: 73, column: 3, scope: !221)
!227 = !DILocation(line: 77, column: 11, scope: !39)
!228 = !DILocation(line: 80, column: 23, scope: !39)
!229 = !DILocation(line: 80, column: 15, scope: !39)
!230 = !DILocation(line: 80, column: 21, scope: !39)
!231 = !DILocation(line: 82, column: 47, scope: !232)
!232 = distinct !DILexicalBlock(scope: !39, file: !1, line: 82, column: 6)
!233 = !DILocation(line: 82, column: 53, scope: !232)
!234 = !DILocation(line: 82, column: 51, scope: !232)
!235 = !DILocation(line: 82, column: 6, scope: !232)
!236 = !DILocation(line: 83, column: 4, scope: !232)
!237 = !DILocation(line: 82, column: 6, scope: !39)
!238 = !DILocation(line: 84, column: 3, scope: !232)
!239 = !DILocation(line: 86, column: 10, scope: !39)
!240 = !DILocation(line: 89, column: 16, scope: !39)
!241 = !DILocation(line: 89, column: 8, scope: !39)
!242 = !DILocation(line: 89, column: 14, scope: !39)
!243 = !DILocation(line: 90, column: 18, scope: !39)
!244 = !DILocation(line: 90, column: 8, scope: !39)
!245 = !DILocation(line: 90, column: 16, scope: !39)
!246 = !DILocation(line: 92, column: 6, scope: !247)
!247 = distinct !DILexicalBlock(scope: !39, file: !1, line: 92, column: 6)
!248 = !DILocation(line: 92, column: 14, scope: !247)
!249 = !DILocation(line: 92, column: 6, scope: !39)
!250 = !DILocation(line: 93, column: 3, scope: !247)
!251 = !DILocalVariable(name: "ret_", scope: !252, file: !1, line: 93, type: !253)
!252 = distinct !DILexicalBlock(scope: !247, file: !1, line: 93, column: 3)
!253 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !42)
!254 = !DILocation(line: 93, column: 3, scope: !252)
!255 = !DILocation(line: 93, column: 3, scope: !256)
!256 = !DILexicalBlockFile(scope: !252, file: !1, discriminator: 1)
!257 = !DILocation(line: 93, column: 3, scope: !258)
!258 = !DILexicalBlockFile(scope: !259, file: !1, discriminator: 2)
!259 = distinct !DILexicalBlock(scope: !252, file: !1, line: 93, column: 3)
!260 = !DILocation(line: 93, column: 3, scope: !261)
!261 = !DILexicalBlockFile(scope: !252, file: !1, discriminator: 3)
!262 = !DILocation(line: 93, column: 3, scope: !263)
!263 = !DILexicalBlockFile(scope: !252, file: !1, discriminator: 4)
!264 = !DILocalVariable(name: "ret", scope: !265, file: !1, line: 98, type: !42)
!265 = distinct !DILexicalBlock(scope: !39, file: !1, line: 97, column: 2)
!266 = !DILocation(line: 98, column: 12, scope: !265)
!267 = !DILocalVariable(name: "i", scope: !265, file: !1, line: 103, type: !268)
!268 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !269, size: 64, align: 64)
!269 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_index", file: !270, line: 37, baseType: !271)
!270 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/index.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!271 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_index_s", file: !270, line: 37, flags: DIFlagFwdDecl)
!272 = !DILocation(line: 103, column: 15, scope: !265)
!273 = !DILocation(line: 103, column: 35, scope: !265)
!274 = !DILocation(line: 103, column: 19, scope: !265)
!275 = !DILocation(line: 104, column: 7, scope: !276)
!276 = distinct !DILexicalBlock(scope: !265, file: !1, line: 104, column: 7)
!277 = !DILocation(line: 104, column: 9, scope: !276)
!278 = !DILocation(line: 104, column: 7, scope: !265)
!279 = !DILocation(line: 105, column: 4, scope: !276)
!280 = !DILocation(line: 107, column: 7, scope: !265)
!281 = !DILocation(line: 109, column: 7, scope: !282)
!282 = distinct !DILexicalBlock(scope: !265, file: !1, line: 109, column: 7)
!283 = !DILocation(line: 109, column: 15, scope: !282)
!284 = !DILocation(line: 109, column: 7, scope: !265)
!285 = !DILocation(line: 110, column: 28, scope: !282)
!286 = !DILocation(line: 110, column: 31, scope: !282)
!287 = !DILocation(line: 111, column: 6, scope: !282)
!288 = !DILocation(line: 112, column: 12, scope: !282)
!289 = !DILocation(line: 110, column: 10, scope: !282)
!290 = !DILocation(line: 110, column: 8, scope: !282)
!291 = !DILocation(line: 110, column: 4, scope: !282)
!292 = !DILocation(line: 116, column: 7, scope: !293)
!293 = distinct !DILexicalBlock(scope: !265, file: !1, line: 116, column: 7)
!294 = !DILocation(line: 116, column: 11, scope: !293)
!295 = !DILocation(line: 116, column: 7, scope: !265)
!296 = !DILocation(line: 118, column: 6, scope: !297)
!297 = distinct !DILexicalBlock(scope: !293, file: !1, line: 116, column: 23)
!298 = !DILocation(line: 118, column: 9, scope: !297)
!299 = !DILocation(line: 118, column: 24, scope: !297)
!300 = !DILocation(line: 117, column: 10, scope: !297)
!301 = !DILocation(line: 117, column: 8, scope: !297)
!302 = !DILocation(line: 120, column: 49, scope: !297)
!303 = !DILocation(line: 120, column: 33, scope: !297)
!304 = !DILocation(line: 120, column: 17, scope: !297)
!305 = !DILocation(line: 120, column: 31, scope: !297)
!306 = !DILocation(line: 121, column: 3, scope: !297)
!307 = !DILocation(line: 123, column: 18, scope: !265)
!308 = !DILocation(line: 123, column: 21, scope: !265)
!309 = !DILocation(line: 123, column: 3, scope: !265)
!310 = !DILocation(line: 125, column: 7, scope: !311)
!311 = distinct !DILexicalBlock(scope: !265, file: !1, line: 125, column: 7)
!312 = !DILocation(line: 125, column: 11, scope: !311)
!313 = !DILocation(line: 125, column: 7, scope: !265)
!314 = !DILocation(line: 126, column: 11, scope: !311)
!315 = !DILocation(line: 126, column: 4, scope: !311)
!316 = !DILocation(line: 130, column: 47, scope: !317)
!317 = distinct !DILexicalBlock(scope: !39, file: !1, line: 130, column: 6)
!318 = !DILocation(line: 130, column: 53, scope: !317)
!319 = !DILocation(line: 130, column: 51, scope: !317)
!320 = !DILocation(line: 130, column: 6, scope: !317)
!321 = !DILocation(line: 131, column: 4, scope: !317)
!322 = !DILocation(line: 130, column: 6, scope: !39)
!323 = !DILocation(line: 132, column: 3, scope: !317)
!324 = !DILocation(line: 134, column: 10, scope: !39)
!325 = !DILocation(line: 138, column: 17, scope: !39)
!326 = !DILocation(line: 138, column: 3, scope: !39)
!327 = !DILocation(line: 138, column: 15, scope: !39)
!328 = !DILocation(line: 139, column: 2, scope: !39)
!329 = !DILocation(line: 140, column: 1, scope: !39)
