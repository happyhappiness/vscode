; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/index_hash.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_index_hash_s = type { i32, %struct.lzma_index_hash_info, %struct.lzma_index_hash_info, i64, i64, i64, i64, i32 }
%struct.lzma_index_hash_info = type { i64, i64, i64, i64, %struct.lzma_check_state }
%struct.lzma_check_state = type { %union.anon, %union.anon.0 }
%union.anon = type { [8 x i64] }
%union.anon.0 = type { %struct.anon }
%struct.anon = type { [8 x i32], i64 }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }

@.str = private unnamed_addr constant [2 x i8] c"0\00", align 1
@.str.1 = private unnamed_addr constant [82 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/index_hash.c\00", align 1
@__PRETTY_FUNCTION__.lzma_index_hash_decode = private unnamed_addr constant [86 x i8] c"lzma_ret lzma_index_hash_decode(lzma_index_hash *, const uint8_t *, size_t *, size_t)\00", align 1
@.str.2 = private unnamed_addr constant [38 x i8] c"vli <= ((18446744073709551615UL) / 2)\00", align 1
@.str.3 = private unnamed_addr constant [77 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/index.h\00", align 1
@__PRETTY_FUNCTION__.vli_ceil4 = private unnamed_addr constant [29 x i8] c"lzma_vli vli_ceil4(lzma_vli)\00", align 1

; Function Attrs: nounwind uwtable
define %struct.lzma_index_hash_s* @lzma_index_hash_init(%struct.lzma_index_hash_s* %index_hash, %struct.lzma_allocator* %allocator) #0 !dbg !98 {
entry:
  %retval = alloca %struct.lzma_index_hash_s*, align 8
  %index_hash.addr = alloca %struct.lzma_index_hash_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  store %struct.lzma_index_hash_s* %index_hash, %struct.lzma_index_hash_s** %index_hash.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_hash_s** %index_hash.addr, metadata !152, metadata !153), !dbg !154
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !155, metadata !153), !dbg !156
  %0 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !157
  %cmp = icmp eq %struct.lzma_index_hash_s* %0, null, !dbg !159
  br i1 %cmp, label %if.then, label %if.end3, !dbg !160

if.then:                                          ; preds = %entry
  %1 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !161
  %call = call noalias i8* @lzma_alloc(i64 320, %struct.lzma_allocator* %1), !dbg !163
  %2 = bitcast i8* %call to %struct.lzma_index_hash_s*, !dbg !163
  store %struct.lzma_index_hash_s* %2, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !164
  %3 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !165
  %cmp1 = icmp eq %struct.lzma_index_hash_s* %3, null, !dbg !167
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !168

if.then2:                                         ; preds = %if.then
  store %struct.lzma_index_hash_s* null, %struct.lzma_index_hash_s** %retval, align 8, !dbg !169
  br label %return, !dbg !169

if.end:                                           ; preds = %if.then
  br label %if.end3, !dbg !170

if.end3:                                          ; preds = %if.end, %entry
  %4 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !171
  %sequence = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %4, i32 0, i32 0, !dbg !172
  store i32 0, i32* %sequence, align 8, !dbg !173
  %5 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !174
  %blocks = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %5, i32 0, i32 1, !dbg !175
  %blocks_size = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %blocks, i32 0, i32 0, !dbg !176
  store i64 0, i64* %blocks_size, align 8, !dbg !177
  %6 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !178
  %blocks4 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %6, i32 0, i32 1, !dbg !179
  %uncompressed_size = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %blocks4, i32 0, i32 1, !dbg !180
  store i64 0, i64* %uncompressed_size, align 8, !dbg !181
  %7 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !182
  %blocks5 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %7, i32 0, i32 1, !dbg !183
  %count = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %blocks5, i32 0, i32 2, !dbg !184
  store i64 0, i64* %count, align 8, !dbg !185
  %8 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !186
  %blocks6 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %8, i32 0, i32 1, !dbg !187
  %index_list_size = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %blocks6, i32 0, i32 3, !dbg !188
  store i64 0, i64* %index_list_size, align 8, !dbg !189
  %9 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !190
  %records = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %9, i32 0, i32 2, !dbg !191
  %blocks_size7 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %records, i32 0, i32 0, !dbg !192
  store i64 0, i64* %blocks_size7, align 8, !dbg !193
  %10 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !194
  %records8 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %10, i32 0, i32 2, !dbg !195
  %uncompressed_size9 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %records8, i32 0, i32 1, !dbg !196
  store i64 0, i64* %uncompressed_size9, align 8, !dbg !197
  %11 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !198
  %records10 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %11, i32 0, i32 2, !dbg !199
  %count11 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %records10, i32 0, i32 2, !dbg !200
  store i64 0, i64* %count11, align 8, !dbg !201
  %12 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !202
  %records12 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %12, i32 0, i32 2, !dbg !203
  %index_list_size13 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %records12, i32 0, i32 3, !dbg !204
  store i64 0, i64* %index_list_size13, align 8, !dbg !205
  %13 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !206
  %unpadded_size = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %13, i32 0, i32 4, !dbg !207
  store i64 0, i64* %unpadded_size, align 8, !dbg !208
  %14 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !209
  %uncompressed_size14 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %14, i32 0, i32 5, !dbg !210
  store i64 0, i64* %uncompressed_size14, align 8, !dbg !211
  %15 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !212
  %pos = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %15, i32 0, i32 6, !dbg !213
  store i64 0, i64* %pos, align 8, !dbg !214
  %16 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !215
  %crc32 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %16, i32 0, i32 7, !dbg !216
  store i32 0, i32* %crc32, align 8, !dbg !217
  %17 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !218
  %blocks15 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %17, i32 0, i32 1, !dbg !219
  %check = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %blocks15, i32 0, i32 4, !dbg !220
  call void @lzma_check_init(%struct.lzma_check_state* %check, i32 10), !dbg !221
  %18 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !222
  %records16 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %18, i32 0, i32 2, !dbg !223
  %check17 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %records16, i32 0, i32 4, !dbg !224
  call void @lzma_check_init(%struct.lzma_check_state* %check17, i32 10), !dbg !225
  %19 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !226
  store %struct.lzma_index_hash_s* %19, %struct.lzma_index_hash_s** %retval, align 8, !dbg !227
  br label %return, !dbg !227

return:                                           ; preds = %if.end3, %if.then2
  %20 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %retval, align 8, !dbg !228
  ret %struct.lzma_index_hash_s* %20, !dbg !228
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare noalias i8* @lzma_alloc(i64, %struct.lzma_allocator*) #2

declare void @lzma_check_init(%struct.lzma_check_state*, i32) #2

; Function Attrs: nounwind uwtable
define void @lzma_index_hash_end(%struct.lzma_index_hash_s* %index_hash, %struct.lzma_allocator* %allocator) #0 !dbg !118 {
entry:
  %index_hash.addr = alloca %struct.lzma_index_hash_s*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  store %struct.lzma_index_hash_s* %index_hash, %struct.lzma_index_hash_s** %index_hash.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_hash_s** %index_hash.addr, metadata !229, metadata !153), !dbg !230
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !231, metadata !153), !dbg !232
  %0 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !233
  %1 = bitcast %struct.lzma_index_hash_s* %0 to i8*, !dbg !233
  %2 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !234
  call void @lzma_free(i8* %1, %struct.lzma_allocator* %2), !dbg !235
  ret void, !dbg !236
}

declare void @lzma_free(i8*, %struct.lzma_allocator*) #2

; Function Attrs: nounwind readonly uwtable
define i64 @lzma_index_hash_size(%struct.lzma_index_hash_s* %index_hash) #3 !dbg !121 {
entry:
  %index_hash.addr = alloca %struct.lzma_index_hash_s*, align 8
  store %struct.lzma_index_hash_s* %index_hash, %struct.lzma_index_hash_s** %index_hash.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_hash_s** %index_hash.addr, metadata !237, metadata !153), !dbg !238
  %0 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !239
  %blocks = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %0, i32 0, i32 1, !dbg !240
  %count = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %blocks, i32 0, i32 2, !dbg !241
  %1 = load i64, i64* %count, align 8, !dbg !241
  %2 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !242
  %blocks1 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %2, i32 0, i32 1, !dbg !243
  %index_list_size = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %blocks1, i32 0, i32 3, !dbg !244
  %3 = load i64, i64* %index_list_size, align 8, !dbg !244
  %call = call i64 @index_size(i64 %1, i64 %3), !dbg !245
  ret i64 %call, !dbg !246
}

; Function Attrs: inlinehint nounwind uwtable
define internal i64 @index_size(i64 %count, i64 %index_list_size) #4 !dbg !134 {
entry:
  %count.addr = alloca i64, align 8
  %index_list_size.addr = alloca i64, align 8
  store i64 %count, i64* %count.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %count.addr, metadata !247, metadata !153), !dbg !248
  store i64 %index_list_size, i64* %index_list_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %index_list_size.addr, metadata !249, metadata !153), !dbg !250
  %0 = load i64, i64* %count.addr, align 8, !dbg !251
  %1 = load i64, i64* %index_list_size.addr, align 8, !dbg !252
  %call = call i64 @index_size_unpadded(i64 %0, i64 %1), !dbg !253
  %call1 = call i64 @vli_ceil4(i64 %call), !dbg !254
  ret i64 %call1, !dbg !256
}

; Function Attrs: nounwind uwtable
define i32 @lzma_index_hash_append(%struct.lzma_index_hash_s* %index_hash, i64 %unpadded_size, i64 %uncompressed_size) #0 !dbg !126 {
entry:
  %retval = alloca i32, align 4
  %index_hash.addr = alloca %struct.lzma_index_hash_s*, align 8
  %unpadded_size.addr = alloca i64, align 8
  %uncompressed_size.addr = alloca i64, align 8
  %ret_ = alloca i32, align 4
  store %struct.lzma_index_hash_s* %index_hash, %struct.lzma_index_hash_s** %index_hash.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_hash_s** %index_hash.addr, metadata !257, metadata !153), !dbg !258
  store i64 %unpadded_size, i64* %unpadded_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %unpadded_size.addr, metadata !259, metadata !153), !dbg !260
  store i64 %uncompressed_size, i64* %uncompressed_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %uncompressed_size.addr, metadata !261, metadata !153), !dbg !262
  %0 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !263
  %sequence = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %0, i32 0, i32 0, !dbg !265
  %1 = load i32, i32* %sequence, align 8, !dbg !265
  %cmp = icmp ne i32 %1, 0, !dbg !266
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !267

lor.lhs.false:                                    ; preds = %entry
  %2 = load i64, i64* %unpadded_size.addr, align 8, !dbg !268
  %cmp1 = icmp ult i64 %2, 5, !dbg !270
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !271

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %3 = load i64, i64* %unpadded_size.addr, align 8, !dbg !272
  %cmp3 = icmp ugt i64 %3, 9223372036854775804, !dbg !273
  br i1 %cmp3, label %if.then, label %lor.lhs.false4, !dbg !274

lor.lhs.false4:                                   ; preds = %lor.lhs.false2
  %4 = load i64, i64* %uncompressed_size.addr, align 8, !dbg !275
  %cmp5 = icmp ugt i64 %4, 9223372036854775807, !dbg !276
  br i1 %cmp5, label %if.then, label %if.end, !dbg !277

if.then:                                          ; preds = %lor.lhs.false4, %lor.lhs.false2, %lor.lhs.false, %entry
  store i32 11, i32* %retval, align 4, !dbg !279
  br label %return, !dbg !279

if.end:                                           ; preds = %lor.lhs.false4
  br label %do.body, !dbg !280

do.body:                                          ; preds = %if.end
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !281, metadata !153), !dbg !284
  %5 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !285
  %blocks = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %5, i32 0, i32 1, !dbg !285
  %6 = load i64, i64* %unpadded_size.addr, align 8, !dbg !285
  %7 = load i64, i64* %uncompressed_size.addr, align 8, !dbg !285
  %call = call i32 @hash_append(%struct.lzma_index_hash_info* %blocks, i64 %6, i64 %7), !dbg !285
  store i32 %call, i32* %ret_, align 4, !dbg !285
  %8 = load i32, i32* %ret_, align 4, !dbg !285
  %cmp6 = icmp ne i32 %8, 0, !dbg !285
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !285

if.then7:                                         ; preds = %do.body
  %9 = load i32, i32* %ret_, align 4, !dbg !287
  store i32 %9, i32* %retval, align 4, !dbg !287
  br label %return, !dbg !287

if.end8:                                          ; preds = %do.body
  br label %do.end, !dbg !290

do.end:                                           ; preds = %if.end8
  %10 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !292
  %blocks9 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %10, i32 0, i32 1, !dbg !294
  %blocks_size = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %blocks9, i32 0, i32 0, !dbg !295
  %11 = load i64, i64* %blocks_size, align 8, !dbg !295
  %cmp10 = icmp ugt i64 %11, 9223372036854775807, !dbg !296
  br i1 %cmp10, label %if.then29, label %lor.lhs.false11, !dbg !297

lor.lhs.false11:                                  ; preds = %do.end
  %12 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !298
  %blocks12 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %12, i32 0, i32 1, !dbg !300
  %uncompressed_size13 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %blocks12, i32 0, i32 1, !dbg !301
  %13 = load i64, i64* %uncompressed_size13, align 8, !dbg !301
  %cmp14 = icmp ugt i64 %13, 9223372036854775807, !dbg !302
  br i1 %cmp14, label %if.then29, label %lor.lhs.false15, !dbg !303

lor.lhs.false15:                                  ; preds = %lor.lhs.false11
  %14 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !304
  %blocks16 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %14, i32 0, i32 1, !dbg !305
  %count = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %blocks16, i32 0, i32 2, !dbg !306
  %15 = load i64, i64* %count, align 8, !dbg !306
  %16 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !307
  %blocks17 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %16, i32 0, i32 1, !dbg !308
  %index_list_size = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %blocks17, i32 0, i32 3, !dbg !309
  %17 = load i64, i64* %index_list_size, align 8, !dbg !309
  %call18 = call i64 @index_size(i64 %15, i64 %17), !dbg !310
  %cmp19 = icmp ugt i64 %call18, 17179869184, !dbg !311
  br i1 %cmp19, label %if.then29, label %lor.lhs.false20, !dbg !312

lor.lhs.false20:                                  ; preds = %lor.lhs.false15
  %18 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !313
  %blocks21 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %18, i32 0, i32 1, !dbg !314
  %blocks_size22 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %blocks21, i32 0, i32 0, !dbg !315
  %19 = load i64, i64* %blocks_size22, align 8, !dbg !315
  %20 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !316
  %blocks23 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %20, i32 0, i32 1, !dbg !317
  %count24 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %blocks23, i32 0, i32 2, !dbg !318
  %21 = load i64, i64* %count24, align 8, !dbg !318
  %22 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !319
  %blocks25 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %22, i32 0, i32 1, !dbg !320
  %index_list_size26 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %blocks25, i32 0, i32 3, !dbg !321
  %23 = load i64, i64* %index_list_size26, align 8, !dbg !321
  %call27 = call i64 @index_stream_size(i64 %19, i64 %21, i64 %23), !dbg !322
  %cmp28 = icmp ugt i64 %call27, 9223372036854775807, !dbg !323
  br i1 %cmp28, label %if.then29, label %if.end30, !dbg !324

if.then29:                                        ; preds = %lor.lhs.false20, %lor.lhs.false15, %lor.lhs.false11, %do.end
  store i32 9, i32* %retval, align 4, !dbg !325
  br label %return, !dbg !325

if.end30:                                         ; preds = %lor.lhs.false20
  store i32 0, i32* %retval, align 4, !dbg !326
  br label %return, !dbg !326

return:                                           ; preds = %if.end30, %if.then29, %if.then7, %if.then
  %24 = load i32, i32* %retval, align 4, !dbg !327
  ret i32 %24, !dbg !327
}

; Function Attrs: nounwind uwtable
define internal i32 @hash_append(%struct.lzma_index_hash_info* %info, i64 %unpadded_size, i64 %uncompressed_size) #0 !dbg !141 {
entry:
  %info.addr = alloca %struct.lzma_index_hash_info*, align 8
  %unpadded_size.addr = alloca i64, align 8
  %uncompressed_size.addr = alloca i64, align 8
  %sizes = alloca [2 x i64], align 16
  store %struct.lzma_index_hash_info* %info, %struct.lzma_index_hash_info** %info.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_hash_info** %info.addr, metadata !328, metadata !153), !dbg !329
  store i64 %unpadded_size, i64* %unpadded_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %unpadded_size.addr, metadata !330, metadata !153), !dbg !331
  store i64 %uncompressed_size, i64* %uncompressed_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %uncompressed_size.addr, metadata !332, metadata !153), !dbg !333
  call void @llvm.dbg.declare(metadata [2 x i64]* %sizes, metadata !334, metadata !153), !dbg !339
  %arrayinit.begin = getelementptr inbounds [2 x i64], [2 x i64]* %sizes, i64 0, i64 0, !dbg !340
  %0 = load i64, i64* %unpadded_size.addr, align 8, !dbg !341
  store i64 %0, i64* %arrayinit.begin, align 8, !dbg !340
  %arrayinit.element = getelementptr inbounds i64, i64* %arrayinit.begin, i64 1, !dbg !340
  %1 = load i64, i64* %uncompressed_size.addr, align 8, !dbg !342
  store i64 %1, i64* %arrayinit.element, align 8, !dbg !340
  %2 = load i64, i64* %unpadded_size.addr, align 8, !dbg !343
  %call = call i64 @vli_ceil4(i64 %2), !dbg !344
  %3 = load %struct.lzma_index_hash_info*, %struct.lzma_index_hash_info** %info.addr, align 8, !dbg !345
  %blocks_size = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %3, i32 0, i32 0, !dbg !346
  %4 = load i64, i64* %blocks_size, align 8, !dbg !347
  %add = add i64 %4, %call, !dbg !347
  store i64 %add, i64* %blocks_size, align 8, !dbg !347
  %5 = load i64, i64* %uncompressed_size.addr, align 8, !dbg !348
  %6 = load %struct.lzma_index_hash_info*, %struct.lzma_index_hash_info** %info.addr, align 8, !dbg !349
  %uncompressed_size1 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %6, i32 0, i32 1, !dbg !350
  %7 = load i64, i64* %uncompressed_size1, align 8, !dbg !351
  %add2 = add i64 %7, %5, !dbg !351
  store i64 %add2, i64* %uncompressed_size1, align 8, !dbg !351
  %8 = load i64, i64* %unpadded_size.addr, align 8, !dbg !352
  %call3 = call i32 @lzma_vli_size(i64 %8) #9, !dbg !353
  %9 = load i64, i64* %uncompressed_size.addr, align 8, !dbg !354
  %call4 = call i32 @lzma_vli_size(i64 %9) #9, !dbg !355
  %add5 = add i32 %call3, %call4, !dbg !356
  %conv = zext i32 %add5 to i64, !dbg !353
  %10 = load %struct.lzma_index_hash_info*, %struct.lzma_index_hash_info** %info.addr, align 8, !dbg !357
  %index_list_size = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %10, i32 0, i32 3, !dbg !358
  %11 = load i64, i64* %index_list_size, align 8, !dbg !359
  %add6 = add i64 %11, %conv, !dbg !359
  store i64 %add6, i64* %index_list_size, align 8, !dbg !359
  %12 = load %struct.lzma_index_hash_info*, %struct.lzma_index_hash_info** %info.addr, align 8, !dbg !360
  %count = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %12, i32 0, i32 2, !dbg !361
  %13 = load i64, i64* %count, align 8, !dbg !362
  %inc = add i64 %13, 1, !dbg !362
  store i64 %inc, i64* %count, align 8, !dbg !362
  %14 = load %struct.lzma_index_hash_info*, %struct.lzma_index_hash_info** %info.addr, align 8, !dbg !363
  %check = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %14, i32 0, i32 4, !dbg !364
  %arraydecay = getelementptr inbounds [2 x i64], [2 x i64]* %sizes, i32 0, i32 0, !dbg !365
  %15 = bitcast i64* %arraydecay to i8*, !dbg !366
  call void @lzma_check_update(%struct.lzma_check_state* %check, i32 10, i8* %15, i64 16), !dbg !367
  ret i32 0, !dbg !368
}

; Function Attrs: inlinehint nounwind uwtable
define internal i64 @index_stream_size(i64 %blocks_size, i64 %count, i64 %index_list_size) #4 !dbg !145 {
entry:
  %blocks_size.addr = alloca i64, align 8
  %count.addr = alloca i64, align 8
  %index_list_size.addr = alloca i64, align 8
  store i64 %blocks_size, i64* %blocks_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %blocks_size.addr, metadata !369, metadata !153), !dbg !370
  store i64 %count, i64* %count.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %count.addr, metadata !371, metadata !153), !dbg !372
  store i64 %index_list_size, i64* %index_list_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %index_list_size.addr, metadata !373, metadata !153), !dbg !374
  %0 = load i64, i64* %blocks_size.addr, align 8, !dbg !375
  %add = add i64 12, %0, !dbg !376
  %1 = load i64, i64* %count.addr, align 8, !dbg !377
  %2 = load i64, i64* %index_list_size.addr, align 8, !dbg !378
  %call = call i64 @index_size(i64 %1, i64 %2), !dbg !379
  %add1 = add i64 %add, %call, !dbg !380
  %add2 = add i64 %add1, 12, !dbg !381
  ret i64 %add2, !dbg !382
}

; Function Attrs: nounwind uwtable
define i32 @lzma_index_hash_decode(%struct.lzma_index_hash_s* %index_hash, i8* %in, i64* %in_pos, i64 %in_size) #0 !dbg !130 {
entry:
  %retval = alloca i32, align 4
  %index_hash.addr = alloca %struct.lzma_index_hash_s*, align 8
  %in.addr = alloca i8*, align 8
  %in_pos.addr = alloca i64*, align 8
  %in_size.addr = alloca i64, align 8
  %in_start = alloca i64, align 8
  %ret = alloca i32, align 4
  %size = alloca i64*, align 8
  %ret_ = alloca i32, align 4
  store %struct.lzma_index_hash_s* %index_hash, %struct.lzma_index_hash_s** %index_hash.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_index_hash_s** %index_hash.addr, metadata !383, metadata !153), !dbg !384
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !385, metadata !153), !dbg !386
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !387, metadata !153), !dbg !388
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !389, metadata !153), !dbg !390
  call void @llvm.dbg.declare(metadata i64* %in_start, metadata !391, metadata !153), !dbg !392
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !393, metadata !153), !dbg !394
  %0 = load i64*, i64** %in_pos.addr, align 8, !dbg !395
  %1 = load i64, i64* %0, align 8, !dbg !397
  %2 = load i64, i64* %in_size.addr, align 8, !dbg !398
  %cmp = icmp uge i64 %1, %2, !dbg !399
  br i1 %cmp, label %if.then, label %if.end, !dbg !400

if.then:                                          ; preds = %entry
  store i32 10, i32* %retval, align 4, !dbg !401
  br label %return, !dbg !401

if.end:                                           ; preds = %entry
  %3 = load i64*, i64** %in_pos.addr, align 8, !dbg !402
  %4 = load i64, i64* %3, align 8, !dbg !403
  store i64 %4, i64* %in_start, align 8, !dbg !404
  store i32 0, i32* %ret, align 4, !dbg !405
  br label %while.cond, !dbg !406

while.cond:                                       ; preds = %sw.epilog, %if.end
  %5 = load i64*, i64** %in_pos.addr, align 8, !dbg !407
  %6 = load i64, i64* %5, align 8, !dbg !409
  %7 = load i64, i64* %in_size.addr, align 8, !dbg !410
  %cmp1 = icmp ult i64 %6, %7, !dbg !411
  br i1 %cmp1, label %while.body, label %while.end, !dbg !412

while.body:                                       ; preds = %while.cond
  %8 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !413
  %sequence = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %8, i32 0, i32 0, !dbg !414
  %9 = load i32, i32* %sequence, align 8, !dbg !414
  switch i32 %9, label %sw.default [
    i32 0, label %sw.bb
    i32 1, label %sw.bb7
    i32 2, label %sw.bb22
    i32 3, label %sw.bb22
    i32 4, label %sw.bb80
    i32 5, label %sw.bb88
    i32 6, label %sw.bb146
  ], !dbg !415

sw.bb:                                            ; preds = %while.body
  %10 = load i64*, i64** %in_pos.addr, align 8, !dbg !416
  %11 = load i64, i64* %10, align 8, !dbg !419
  %inc = add i64 %11, 1, !dbg !419
  store i64 %inc, i64* %10, align 8, !dbg !419
  %12 = load i8*, i8** %in.addr, align 8, !dbg !420
  %arrayidx = getelementptr inbounds i8, i8* %12, i64 %11, !dbg !420
  %13 = load i8, i8* %arrayidx, align 1, !dbg !420
  %conv = zext i8 %13 to i32, !dbg !420
  %cmp2 = icmp ne i32 %conv, 0, !dbg !421
  br i1 %cmp2, label %if.then4, label %if.end5, !dbg !422

if.then4:                                         ; preds = %sw.bb
  store i32 9, i32* %retval, align 4, !dbg !423
  br label %return, !dbg !423

if.end5:                                          ; preds = %sw.bb
  %14 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !424
  %sequence6 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %14, i32 0, i32 0, !dbg !425
  store i32 1, i32* %sequence6, align 8, !dbg !426
  br label %sw.epilog, !dbg !427

sw.bb7:                                           ; preds = %while.body
  %15 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !428
  %remaining = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %15, i32 0, i32 3, !dbg !430
  %16 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !431
  %pos = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %16, i32 0, i32 6, !dbg !432
  %17 = load i8*, i8** %in.addr, align 8, !dbg !433
  %18 = load i64*, i64** %in_pos.addr, align 8, !dbg !434
  %19 = load i64, i64* %in_size.addr, align 8, !dbg !435
  %call = call i32 @lzma_vli_decode(i64* %remaining, i64* %pos, i8* %17, i64* %18, i64 %19) #10, !dbg !436
  store i32 %call, i32* %ret, align 4, !dbg !437
  %20 = load i32, i32* %ret, align 4, !dbg !438
  %cmp8 = icmp ne i32 %20, 1, !dbg !440
  br i1 %cmp8, label %if.then10, label %if.end11, !dbg !441

if.then10:                                        ; preds = %sw.bb7
  br label %out, !dbg !442

if.end11:                                         ; preds = %sw.bb7
  %21 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !443
  %remaining12 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %21, i32 0, i32 3, !dbg !445
  %22 = load i64, i64* %remaining12, align 8, !dbg !445
  %23 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !446
  %blocks = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %23, i32 0, i32 1, !dbg !447
  %count = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %blocks, i32 0, i32 2, !dbg !448
  %24 = load i64, i64* %count, align 8, !dbg !448
  %cmp13 = icmp ne i64 %22, %24, !dbg !449
  br i1 %cmp13, label %if.then15, label %if.end16, !dbg !450

if.then15:                                        ; preds = %if.end11
  store i32 9, i32* %retval, align 4, !dbg !451
  br label %return, !dbg !451

if.end16:                                         ; preds = %if.end11
  store i32 0, i32* %ret, align 4, !dbg !452
  %25 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !453
  %pos17 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %25, i32 0, i32 6, !dbg !454
  store i64 0, i64* %pos17, align 8, !dbg !455
  %26 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !456
  %remaining18 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %26, i32 0, i32 3, !dbg !457
  %27 = load i64, i64* %remaining18, align 8, !dbg !457
  %cmp19 = icmp eq i64 %27, 0, !dbg !458
  %cond = select i1 %cmp19, i32 4, i32 2, !dbg !456
  %28 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !459
  %sequence21 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %28, i32 0, i32 0, !dbg !460
  store i32 %cond, i32* %sequence21, align 8, !dbg !461
  br label %sw.epilog, !dbg !462

sw.bb22:                                          ; preds = %while.body, %while.body
  call void @llvm.dbg.declare(metadata i64** %size, metadata !463, metadata !153), !dbg !466
  %29 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !467
  %sequence23 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %29, i32 0, i32 0, !dbg !468
  %30 = load i32, i32* %sequence23, align 8, !dbg !468
  %cmp24 = icmp eq i32 %30, 2, !dbg !469
  br i1 %cmp24, label %cond.true, label %cond.false, !dbg !467

cond.true:                                        ; preds = %sw.bb22
  %31 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !470
  %unpadded_size = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %31, i32 0, i32 4, !dbg !471
  br label %cond.end, !dbg !472

cond.false:                                       ; preds = %sw.bb22
  %32 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !474
  %uncompressed_size = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %32, i32 0, i32 5, !dbg !475
  br label %cond.end, !dbg !476

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond26 = phi i64* [ %unpadded_size, %cond.true ], [ %uncompressed_size, %cond.false ], !dbg !478
  store i64* %cond26, i64** %size, align 8, !dbg !480
  %33 = load i64*, i64** %size, align 8, !dbg !481
  %34 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !482
  %pos27 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %34, i32 0, i32 6, !dbg !483
  %35 = load i8*, i8** %in.addr, align 8, !dbg !484
  %36 = load i64*, i64** %in_pos.addr, align 8, !dbg !485
  %37 = load i64, i64* %in_size.addr, align 8, !dbg !486
  %call28 = call i32 @lzma_vli_decode(i64* %33, i64* %pos27, i8* %35, i64* %36, i64 %37) #10, !dbg !487
  store i32 %call28, i32* %ret, align 4, !dbg !488
  %38 = load i32, i32* %ret, align 4, !dbg !489
  %cmp29 = icmp ne i32 %38, 1, !dbg !491
  br i1 %cmp29, label %if.then31, label %if.end32, !dbg !492

if.then31:                                        ; preds = %cond.end
  br label %out, !dbg !493

if.end32:                                         ; preds = %cond.end
  store i32 0, i32* %ret, align 4, !dbg !494
  %39 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !495
  %pos33 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %39, i32 0, i32 6, !dbg !496
  store i64 0, i64* %pos33, align 8, !dbg !497
  %40 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !498
  %sequence34 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %40, i32 0, i32 0, !dbg !500
  %41 = load i32, i32* %sequence34, align 8, !dbg !500
  %cmp35 = icmp eq i32 %41, 2, !dbg !501
  br i1 %cmp35, label %if.then37, label %if.else, !dbg !502

if.then37:                                        ; preds = %if.end32
  %42 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !503
  %unpadded_size38 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %42, i32 0, i32 4, !dbg !506
  %43 = load i64, i64* %unpadded_size38, align 8, !dbg !506
  %cmp39 = icmp ult i64 %43, 5, !dbg !507
  br i1 %cmp39, label %if.then44, label %lor.lhs.false, !dbg !508

lor.lhs.false:                                    ; preds = %if.then37
  %44 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !509
  %unpadded_size41 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %44, i32 0, i32 4, !dbg !511
  %45 = load i64, i64* %unpadded_size41, align 8, !dbg !511
  %cmp42 = icmp ugt i64 %45, 9223372036854775804, !dbg !512
  br i1 %cmp42, label %if.then44, label %if.end45, !dbg !513

if.then44:                                        ; preds = %lor.lhs.false, %if.then37
  store i32 9, i32* %retval, align 4, !dbg !515
  br label %return, !dbg !515

if.end45:                                         ; preds = %lor.lhs.false
  %46 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !516
  %sequence46 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %46, i32 0, i32 0, !dbg !517
  store i32 3, i32* %sequence46, align 8, !dbg !518
  br label %if.end79, !dbg !519

if.else:                                          ; preds = %if.end32
  br label %do.body, !dbg !520

do.body:                                          ; preds = %if.else
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !522, metadata !153), !dbg !524
  %47 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !525
  %records = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %47, i32 0, i32 2, !dbg !525
  %48 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !525
  %unpadded_size47 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %48, i32 0, i32 4, !dbg !525
  %49 = load i64, i64* %unpadded_size47, align 8, !dbg !525
  %50 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !525
  %uncompressed_size48 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %50, i32 0, i32 5, !dbg !525
  %51 = load i64, i64* %uncompressed_size48, align 8, !dbg !525
  %call49 = call i32 @hash_append(%struct.lzma_index_hash_info* %records, i64 %49, i64 %51), !dbg !525
  store i32 %call49, i32* %ret_, align 4, !dbg !525
  %52 = load i32, i32* %ret_, align 4, !dbg !525
  %cmp50 = icmp ne i32 %52, 0, !dbg !525
  br i1 %cmp50, label %if.then52, label %if.end53, !dbg !525

if.then52:                                        ; preds = %do.body
  %53 = load i32, i32* %ret_, align 4, !dbg !527
  store i32 %53, i32* %retval, align 4, !dbg !527
  br label %return, !dbg !527

if.end53:                                         ; preds = %do.body
  br label %do.end, !dbg !530

do.end:                                           ; preds = %if.end53
  %54 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !532
  %blocks54 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %54, i32 0, i32 1, !dbg !534
  %blocks_size = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %blocks54, i32 0, i32 0, !dbg !535
  %55 = load i64, i64* %blocks_size, align 8, !dbg !535
  %56 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !536
  %records55 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %56, i32 0, i32 2, !dbg !537
  %blocks_size56 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %records55, i32 0, i32 0, !dbg !538
  %57 = load i64, i64* %blocks_size56, align 8, !dbg !538
  %cmp57 = icmp ult i64 %55, %57, !dbg !539
  br i1 %cmp57, label %if.then72, label %lor.lhs.false59, !dbg !540

lor.lhs.false59:                                  ; preds = %do.end
  %58 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !541
  %blocks60 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %58, i32 0, i32 1, !dbg !543
  %uncompressed_size61 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %blocks60, i32 0, i32 1, !dbg !544
  %59 = load i64, i64* %uncompressed_size61, align 8, !dbg !544
  %60 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !545
  %records62 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %60, i32 0, i32 2, !dbg !546
  %uncompressed_size63 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %records62, i32 0, i32 1, !dbg !547
  %61 = load i64, i64* %uncompressed_size63, align 8, !dbg !547
  %cmp64 = icmp ult i64 %59, %61, !dbg !548
  br i1 %cmp64, label %if.then72, label %lor.lhs.false66, !dbg !549

lor.lhs.false66:                                  ; preds = %lor.lhs.false59
  %62 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !550
  %blocks67 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %62, i32 0, i32 1, !dbg !551
  %index_list_size = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %blocks67, i32 0, i32 3, !dbg !552
  %63 = load i64, i64* %index_list_size, align 8, !dbg !552
  %64 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !553
  %records68 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %64, i32 0, i32 2, !dbg !554
  %index_list_size69 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %records68, i32 0, i32 3, !dbg !555
  %65 = load i64, i64* %index_list_size69, align 8, !dbg !555
  %cmp70 = icmp ult i64 %63, %65, !dbg !556
  br i1 %cmp70, label %if.then72, label %if.end73, !dbg !557

if.then72:                                        ; preds = %lor.lhs.false66, %lor.lhs.false59, %do.end
  store i32 9, i32* %retval, align 4, !dbg !559
  br label %return, !dbg !559

if.end73:                                         ; preds = %lor.lhs.false66
  %66 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !560
  %remaining74 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %66, i32 0, i32 3, !dbg !561
  %67 = load i64, i64* %remaining74, align 8, !dbg !562
  %dec = add i64 %67, -1, !dbg !562
  store i64 %dec, i64* %remaining74, align 8, !dbg !562
  %cmp75 = icmp eq i64 %dec, 0, !dbg !563
  %cond77 = select i1 %cmp75, i32 4, i32 2, !dbg !562
  %68 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !564
  %sequence78 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %68, i32 0, i32 0, !dbg !565
  store i32 %cond77, i32* %sequence78, align 8, !dbg !566
  br label %if.end79

if.end79:                                         ; preds = %if.end73, %if.end45
  br label %sw.epilog, !dbg !567

sw.bb80:                                          ; preds = %while.body
  %69 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !568
  %records81 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %69, i32 0, i32 2, !dbg !569
  %count82 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %records81, i32 0, i32 2, !dbg !570
  %70 = load i64, i64* %count82, align 8, !dbg !570
  %71 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !571
  %records83 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %71, i32 0, i32 2, !dbg !572
  %index_list_size84 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %records83, i32 0, i32 3, !dbg !573
  %72 = load i64, i64* %index_list_size84, align 8, !dbg !573
  %call85 = call i64 @index_size_unpadded(i64 %70, i64 %72), !dbg !574
  %sub = sub i64 4, %call85, !dbg !575
  %and = and i64 %sub, 3, !dbg !576
  %73 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !577
  %pos86 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %73, i32 0, i32 6, !dbg !578
  store i64 %and, i64* %pos86, align 8, !dbg !579
  %74 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !580
  %sequence87 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %74, i32 0, i32 0, !dbg !581
  store i32 5, i32* %sequence87, align 8, !dbg !582
  br label %sw.bb88, !dbg !580

sw.bb88:                                          ; preds = %while.body, %sw.bb80
  %75 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !583
  %pos89 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %75, i32 0, i32 6, !dbg !585
  %76 = load i64, i64* %pos89, align 8, !dbg !585
  %cmp90 = icmp ugt i64 %76, 0, !dbg !586
  br i1 %cmp90, label %if.then92, label %if.end102, !dbg !587

if.then92:                                        ; preds = %sw.bb88
  %77 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !588
  %pos93 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %77, i32 0, i32 6, !dbg !590
  %78 = load i64, i64* %pos93, align 8, !dbg !591
  %dec94 = add i64 %78, -1, !dbg !591
  store i64 %dec94, i64* %pos93, align 8, !dbg !591
  %79 = load i64*, i64** %in_pos.addr, align 8, !dbg !592
  %80 = load i64, i64* %79, align 8, !dbg !594
  %inc95 = add i64 %80, 1, !dbg !594
  store i64 %inc95, i64* %79, align 8, !dbg !594
  %81 = load i8*, i8** %in.addr, align 8, !dbg !595
  %arrayidx96 = getelementptr inbounds i8, i8* %81, i64 %80, !dbg !595
  %82 = load i8, i8* %arrayidx96, align 1, !dbg !595
  %conv97 = zext i8 %82 to i32, !dbg !595
  %cmp98 = icmp ne i32 %conv97, 0, !dbg !596
  br i1 %cmp98, label %if.then100, label %if.end101, !dbg !597

if.then100:                                       ; preds = %if.then92
  store i32 9, i32* %retval, align 4, !dbg !598
  br label %return, !dbg !598

if.end101:                                        ; preds = %if.then92
  br label %sw.epilog, !dbg !599

if.end102:                                        ; preds = %sw.bb88
  %83 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !600
  %blocks103 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %83, i32 0, i32 1, !dbg !602
  %blocks_size104 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %blocks103, i32 0, i32 0, !dbg !603
  %84 = load i64, i64* %blocks_size104, align 8, !dbg !603
  %85 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !604
  %records105 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %85, i32 0, i32 2, !dbg !605
  %blocks_size106 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %records105, i32 0, i32 0, !dbg !606
  %86 = load i64, i64* %blocks_size106, align 8, !dbg !606
  %cmp107 = icmp ne i64 %84, %86, !dbg !607
  br i1 %cmp107, label %if.then123, label %lor.lhs.false109, !dbg !608

lor.lhs.false109:                                 ; preds = %if.end102
  %87 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !609
  %blocks110 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %87, i32 0, i32 1, !dbg !611
  %uncompressed_size111 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %blocks110, i32 0, i32 1, !dbg !612
  %88 = load i64, i64* %uncompressed_size111, align 8, !dbg !612
  %89 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !613
  %records112 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %89, i32 0, i32 2, !dbg !614
  %uncompressed_size113 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %records112, i32 0, i32 1, !dbg !615
  %90 = load i64, i64* %uncompressed_size113, align 8, !dbg !615
  %cmp114 = icmp ne i64 %88, %90, !dbg !616
  br i1 %cmp114, label %if.then123, label %lor.lhs.false116, !dbg !617

lor.lhs.false116:                                 ; preds = %lor.lhs.false109
  %91 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !618
  %blocks117 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %91, i32 0, i32 1, !dbg !619
  %index_list_size118 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %blocks117, i32 0, i32 3, !dbg !620
  %92 = load i64, i64* %index_list_size118, align 8, !dbg !620
  %93 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !621
  %records119 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %93, i32 0, i32 2, !dbg !622
  %index_list_size120 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %records119, i32 0, i32 3, !dbg !623
  %94 = load i64, i64* %index_list_size120, align 8, !dbg !623
  %cmp121 = icmp ne i64 %92, %94, !dbg !624
  br i1 %cmp121, label %if.then123, label %if.end124, !dbg !625

if.then123:                                       ; preds = %lor.lhs.false116, %lor.lhs.false109, %if.end102
  store i32 9, i32* %retval, align 4, !dbg !627
  br label %return, !dbg !627

if.end124:                                        ; preds = %lor.lhs.false116
  %95 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !628
  %blocks125 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %95, i32 0, i32 1, !dbg !629
  %check = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %blocks125, i32 0, i32 4, !dbg !630
  call void @lzma_check_finish(%struct.lzma_check_state* %check, i32 10), !dbg !631
  %96 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !632
  %records126 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %96, i32 0, i32 2, !dbg !633
  %check127 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %records126, i32 0, i32 4, !dbg !634
  call void @lzma_check_finish(%struct.lzma_check_state* %check127, i32 10), !dbg !635
  %97 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !636
  %blocks128 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %97, i32 0, i32 1, !dbg !638
  %check129 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %blocks128, i32 0, i32 4, !dbg !639
  %buffer = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %check129, i32 0, i32 0, !dbg !640
  %u8 = bitcast %union.anon* %buffer to [64 x i8]*, !dbg !641
  %arraydecay = getelementptr inbounds [64 x i8], [64 x i8]* %u8, i32 0, i32 0, !dbg !636
  %98 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !642
  %records130 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %98, i32 0, i32 2, !dbg !643
  %check131 = getelementptr inbounds %struct.lzma_index_hash_info, %struct.lzma_index_hash_info* %records130, i32 0, i32 4, !dbg !644
  %buffer132 = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %check131, i32 0, i32 0, !dbg !645
  %u8133 = bitcast %union.anon* %buffer132 to [64 x i8]*, !dbg !646
  %arraydecay134 = getelementptr inbounds [64 x i8], [64 x i8]* %u8133, i32 0, i32 0, !dbg !642
  %call135 = call i32 @lzma_check_size(i32 10) #1, !dbg !647
  %conv136 = zext i32 %call135 to i64, !dbg !647
  %call137 = call i32 @memcmp(i8* %arraydecay, i8* %arraydecay134, i64 %conv136) #9, !dbg !648
  %cmp138 = icmp ne i32 %call137, 0, !dbg !649
  br i1 %cmp138, label %if.then140, label %if.end141, !dbg !650

if.then140:                                       ; preds = %if.end124
  store i32 9, i32* %retval, align 4, !dbg !651
  br label %return, !dbg !651

if.end141:                                        ; preds = %if.end124
  %99 = load i8*, i8** %in.addr, align 8, !dbg !652
  %100 = load i64, i64* %in_start, align 8, !dbg !653
  %add.ptr = getelementptr inbounds i8, i8* %99, i64 %100, !dbg !654
  %101 = load i64*, i64** %in_pos.addr, align 8, !dbg !655
  %102 = load i64, i64* %101, align 8, !dbg !656
  %103 = load i64, i64* %in_start, align 8, !dbg !657
  %sub142 = sub i64 %102, %103, !dbg !658
  %104 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !659
  %crc32 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %104, i32 0, i32 7, !dbg !660
  %105 = load i32, i32* %crc32, align 8, !dbg !660
  %call143 = call i32 @lzma_crc32(i8* %add.ptr, i64 %sub142, i32 %105) #9, !dbg !661
  %106 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !662
  %crc32144 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %106, i32 0, i32 7, !dbg !663
  store i32 %call143, i32* %crc32144, align 8, !dbg !664
  %107 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !665
  %sequence145 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %107, i32 0, i32 0, !dbg !666
  store i32 6, i32* %sequence145, align 8, !dbg !667
  br label %sw.bb146, !dbg !665

sw.bb146:                                         ; preds = %while.body, %if.end141
  br label %do.body147, !dbg !668

do.body147:                                       ; preds = %do.cond, %sw.bb146
  %108 = load i64*, i64** %in_pos.addr, align 8, !dbg !669
  %109 = load i64, i64* %108, align 8, !dbg !672
  %110 = load i64, i64* %in_size.addr, align 8, !dbg !673
  %cmp148 = icmp eq i64 %109, %110, !dbg !674
  br i1 %cmp148, label %if.then150, label %if.end151, !dbg !675

if.then150:                                       ; preds = %do.body147
  store i32 0, i32* %retval, align 4, !dbg !676
  br label %return, !dbg !676

if.end151:                                        ; preds = %do.body147
  %111 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !677
  %crc32152 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %111, i32 0, i32 7, !dbg !679
  %112 = load i32, i32* %crc32152, align 8, !dbg !679
  %113 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !680
  %pos153 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %113, i32 0, i32 6, !dbg !681
  %114 = load i64, i64* %pos153, align 8, !dbg !681
  %mul = mul i64 %114, 8, !dbg !682
  %sh_prom = trunc i64 %mul to i32, !dbg !683
  %shr = lshr i32 %112, %sh_prom, !dbg !683
  %and154 = and i32 %shr, 255, !dbg !684
  %115 = load i64*, i64** %in_pos.addr, align 8, !dbg !685
  %116 = load i64, i64* %115, align 8, !dbg !686
  %inc155 = add i64 %116, 1, !dbg !686
  store i64 %inc155, i64* %115, align 8, !dbg !686
  %117 = load i8*, i8** %in.addr, align 8, !dbg !687
  %arrayidx156 = getelementptr inbounds i8, i8* %117, i64 %116, !dbg !687
  %118 = load i8, i8* %arrayidx156, align 1, !dbg !687
  %conv157 = zext i8 %118 to i32, !dbg !687
  %cmp158 = icmp ne i32 %and154, %conv157, !dbg !688
  br i1 %cmp158, label %if.then160, label %if.end161, !dbg !689

if.then160:                                       ; preds = %if.end151
  store i32 9, i32* %retval, align 4, !dbg !690
  br label %return, !dbg !690

if.end161:                                        ; preds = %if.end151
  br label %do.cond, !dbg !691

do.cond:                                          ; preds = %if.end161
  %119 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !692
  %pos162 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %119, i32 0, i32 6, !dbg !693
  %120 = load i64, i64* %pos162, align 8, !dbg !694
  %inc163 = add i64 %120, 1, !dbg !694
  store i64 %inc163, i64* %pos162, align 8, !dbg !694
  %cmp164 = icmp ult i64 %inc163, 4, !dbg !695
  br i1 %cmp164, label %do.body147, label %do.end166, !dbg !696

do.end166:                                        ; preds = %do.cond
  store i32 1, i32* %retval, align 4, !dbg !697
  br label %return, !dbg !697

sw.default:                                       ; preds = %while.body
  call void @__assert_fail(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([82 x i8], [82 x i8]* @.str.1, i32 0, i32 0), i32 326, i8* getelementptr inbounds ([86 x i8], [86 x i8]* @__PRETTY_FUNCTION__.lzma_index_hash_decode, i32 0, i32 0)) #11, !dbg !698
  unreachable, !dbg !698

sw.epilog:                                        ; preds = %if.end101, %if.end79, %if.end16, %if.end5
  br label %while.cond, !dbg !699

while.end:                                        ; preds = %while.cond
  br label %out, !dbg !701

out:                                              ; preds = %while.end, %if.then31, %if.then10
  %121 = load i8*, i8** %in.addr, align 8, !dbg !703
  %122 = load i64, i64* %in_start, align 8, !dbg !704
  %add.ptr167 = getelementptr inbounds i8, i8* %121, i64 %122, !dbg !705
  %123 = load i64*, i64** %in_pos.addr, align 8, !dbg !706
  %124 = load i64, i64* %123, align 8, !dbg !707
  %125 = load i64, i64* %in_start, align 8, !dbg !708
  %sub168 = sub i64 %124, %125, !dbg !709
  %126 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !710
  %crc32169 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %126, i32 0, i32 7, !dbg !711
  %127 = load i32, i32* %crc32169, align 8, !dbg !711
  %call170 = call i32 @lzma_crc32(i8* %add.ptr167, i64 %sub168, i32 %127) #9, !dbg !712
  %128 = load %struct.lzma_index_hash_s*, %struct.lzma_index_hash_s** %index_hash.addr, align 8, !dbg !713
  %crc32171 = getelementptr inbounds %struct.lzma_index_hash_s, %struct.lzma_index_hash_s* %128, i32 0, i32 7, !dbg !714
  store i32 %call170, i32* %crc32171, align 8, !dbg !715
  %129 = load i32, i32* %ret, align 4, !dbg !716
  store i32 %129, i32* %retval, align 4, !dbg !717
  br label %return, !dbg !717

return:                                           ; preds = %out, %do.end166, %if.then160, %if.then150, %if.then140, %if.then123, %if.then100, %if.then72, %if.then52, %if.then44, %if.then15, %if.then4, %if.then
  %130 = load i32, i32* %retval, align 4, !dbg !718
  ret i32 %130, !dbg !718
}

; Function Attrs: nounwind
declare i32 @lzma_vli_decode(i64*, i64*, i8*, i64*, i64) #5

; Function Attrs: inlinehint nounwind uwtable
define internal i64 @index_size_unpadded(i64 %count, i64 %index_list_size) #4 !dbg !148 {
entry:
  %count.addr = alloca i64, align 8
  %index_list_size.addr = alloca i64, align 8
  store i64 %count, i64* %count.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %count.addr, metadata !719, metadata !153), !dbg !720
  store i64 %index_list_size, i64* %index_list_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %index_list_size.addr, metadata !721, metadata !153), !dbg !722
  %0 = load i64, i64* %count.addr, align 8, !dbg !723
  %call = call i32 @lzma_vli_size(i64 %0) #9, !dbg !724
  %add = add i32 1, %call, !dbg !725
  %conv = zext i32 %add to i64, !dbg !726
  %1 = load i64, i64* %index_list_size.addr, align 8, !dbg !727
  %add1 = add i64 %conv, %1, !dbg !728
  %add2 = add i64 %add1, 4, !dbg !729
  ret i64 %add2, !dbg !730
}

declare void @lzma_check_finish(%struct.lzma_check_state*, i32) #2

; Function Attrs: nounwind readonly
declare i32 @memcmp(i8*, i8*, i64) #6

; Function Attrs: nounwind readnone
declare i32 @lzma_check_size(i32) #7

; Function Attrs: nounwind readonly
declare i32 @lzma_crc32(i8*, i64, i32) #6

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #8

; Function Attrs: inlinehint nounwind uwtable
define internal i64 @vli_ceil4(i64 %vli) #4 !dbg !138 {
entry:
  %vli.addr = alloca i64, align 8
  store i64 %vli, i64* %vli.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %vli.addr, metadata !731, metadata !153), !dbg !732
  %0 = load i64, i64* %vli.addr, align 8, !dbg !733
  %cmp = icmp ule i64 %0, 9223372036854775807, !dbg !733
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !733

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !734

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([77 x i8], [77 x i8]* @.str.3, i32 0, i32 0), i32 41, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @__PRETTY_FUNCTION__.vli_ceil4, i32 0, i32 0)) #11, !dbg !736
  unreachable, !dbg !736
                                                  ; No predecessors!
  br label %cond.end, !dbg !738

cond.end:                                         ; preds = %1, %cond.true
  %2 = load i64, i64* %vli.addr, align 8, !dbg !740
  %add = add i64 %2, 3, !dbg !741
  %and = and i64 %add, -4, !dbg !742
  ret i64 %and, !dbg !743
}

; Function Attrs: nounwind readonly
declare i32 @lzma_vli_size(i64) #6

declare void @lzma_check_update(%struct.lzma_check_state*, i32, i8*, i64) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #9 = { nounwind readonly }
attributes #10 = { nounwind }
attributes #11 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!149, !150}
!llvm.ident = !{!151}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !93, subprograms: !97)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/index_hash.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !71, !78}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !4, file: !1, line: 38, size: 32, align: 32, elements: !63)
!4 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_index_hash_s", file: !1, line: 37, size: 2560, align: 64, elements: !5)
!5 = !{!6, !7, !55, !56, !57, !58, !59, !62}
!6 = !DIDerivedType(tag: DW_TAG_member, name: "sequence", scope: !4, file: !1, line: 46, baseType: !3, size: 32, align: 32)
!7 = !DIDerivedType(tag: DW_TAG_member, name: "blocks", scope: !4, file: !1, line: 49, baseType: !8, size: 1088, align: 64, offset: 64)
!8 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_index_hash_info", file: !1, line: 34, baseType: !9)
!9 = !DICompositeType(tag: DW_TAG_structure_type, file: !1, line: 18, size: 1088, align: 64, elements: !10)
!10 = !{!11, !17, !18, !19, !20}
!11 = !DIDerivedType(tag: DW_TAG_member, name: "blocks_size", scope: !9, file: !1, line: 20, baseType: !12, size: 64, align: 64)
!12 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !13, line: 63, baseType: !14)
!13 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!14 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !15, line: 55, baseType: !16)
!15 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!16 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!17 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_size", scope: !9, file: !1, line: 23, baseType: !12, size: 64, align: 64, offset: 64)
!18 = !DIDerivedType(tag: DW_TAG_member, name: "count", scope: !9, file: !1, line: 26, baseType: !12, size: 64, align: 64, offset: 128)
!19 = !DIDerivedType(tag: DW_TAG_member, name: "index_list_size", scope: !9, file: !1, line: 29, baseType: !12, size: 64, align: 64, offset: 192)
!20 = !DIDerivedType(tag: DW_TAG_member, name: "check", scope: !9, file: !1, line: 32, baseType: !21, size: 832, align: 64, offset: 256)
!21 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check_state", file: !22, line: 56, baseType: !23)
!22 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/check/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!23 = !DICompositeType(tag: DW_TAG_structure_type, file: !22, line: 34, size: 832, align: 64, elements: !24)
!24 = !{!25, !44}
!25 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !23, file: !22, line: 40, baseType: !26, size: 512, align: 64)
!26 = !DICompositeType(tag: DW_TAG_union_type, scope: !23, file: !22, line: 36, size: 512, align: 64, elements: !27)
!27 = !{!28, !34, !40}
!28 = !DIDerivedType(tag: DW_TAG_member, name: "u8", scope: !26, file: !22, line: 37, baseType: !29, size: 512, align: 8)
!29 = !DICompositeType(tag: DW_TAG_array_type, baseType: !30, size: 512, align: 8, elements: !32)
!30 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !15, line: 48, baseType: !31)
!31 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!32 = !{!33}
!33 = !DISubrange(count: 64)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "u32", scope: !26, file: !22, line: 38, baseType: !35, size: 512, align: 32)
!35 = !DICompositeType(tag: DW_TAG_array_type, baseType: !36, size: 512, align: 32, elements: !38)
!36 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !15, line: 51, baseType: !37)
!37 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!38 = !{!39}
!39 = !DISubrange(count: 16)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "u64", scope: !26, file: !22, line: 39, baseType: !41, size: 512, align: 64)
!41 = !DICompositeType(tag: DW_TAG_array_type, baseType: !14, size: 512, align: 64, elements: !42)
!42 = !{!43}
!43 = !DISubrange(count: 8)
!44 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !23, file: !22, line: 54, baseType: !45, size: 320, align: 64, offset: 512)
!45 = !DICompositeType(tag: DW_TAG_union_type, scope: !23, file: !22, line: 43, size: 320, align: 64, elements: !46)
!46 = !{!47, !48, !49}
!47 = !DIDerivedType(tag: DW_TAG_member, name: "crc32", scope: !45, file: !22, line: 44, baseType: !36, size: 32, align: 32)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "crc64", scope: !45, file: !22, line: 45, baseType: !14, size: 64, align: 64)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "sha256", scope: !45, file: !22, line: 53, baseType: !50, size: 320, align: 64)
!50 = !DICompositeType(tag: DW_TAG_structure_type, scope: !45, file: !22, line: 47, size: 320, align: 64, elements: !51)
!51 = !{!52, !54}
!52 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !50, file: !22, line: 49, baseType: !53, size: 256, align: 32)
!53 = !DICompositeType(tag: DW_TAG_array_type, baseType: !36, size: 256, align: 32, elements: !42)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !50, file: !22, line: 52, baseType: !14, size: 64, align: 64, offset: 256)
!55 = !DIDerivedType(tag: DW_TAG_member, name: "records", scope: !4, file: !1, line: 52, baseType: !8, size: 1088, align: 64, offset: 1152)
!56 = !DIDerivedType(tag: DW_TAG_member, name: "remaining", scope: !4, file: !1, line: 55, baseType: !12, size: 64, align: 64, offset: 2240)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "unpadded_size", scope: !4, file: !1, line: 58, baseType: !12, size: 64, align: 64, offset: 2304)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "uncompressed_size", scope: !4, file: !1, line: 61, baseType: !12, size: 64, align: 64, offset: 2368)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "pos", scope: !4, file: !1, line: 65, baseType: !60, size: 64, align: 64, offset: 2432)
!60 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !61, line: 62, baseType: !16)
!61 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!62 = !DIDerivedType(tag: DW_TAG_member, name: "crc32", scope: !4, file: !1, line: 68, baseType: !36, size: 32, align: 32, offset: 2496)
!63 = !{!64, !65, !66, !67, !68, !69, !70}
!64 = !DIEnumerator(name: "SEQ_BLOCK", value: 0)
!65 = !DIEnumerator(name: "SEQ_COUNT", value: 1)
!66 = !DIEnumerator(name: "SEQ_UNPADDED", value: 2)
!67 = !DIEnumerator(name: "SEQ_UNCOMPRESSED", value: 3)
!68 = !DIEnumerator(name: "SEQ_PADDING_INIT", value: 4)
!69 = !DIEnumerator(name: "SEQ_PADDING", value: 5)
!70 = !DIEnumerator(name: "SEQ_CRC32", value: 6)
!71 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !72, line: 27, size: 32, align: 32, elements: !73)
!72 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!73 = !{!74, !75, !76, !77}
!74 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!75 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!76 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!77 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!78 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !79, line: 57, size: 32, align: 32, elements: !80)
!79 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/base.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!80 = !{!81, !82, !83, !84, !85, !86, !87, !88, !89, !90, !91, !92}
!81 = !DIEnumerator(name: "LZMA_OK", value: 0)
!82 = !DIEnumerator(name: "LZMA_STREAM_END", value: 1)
!83 = !DIEnumerator(name: "LZMA_NO_CHECK", value: 2)
!84 = !DIEnumerator(name: "LZMA_UNSUPPORTED_CHECK", value: 3)
!85 = !DIEnumerator(name: "LZMA_GET_CHECK", value: 4)
!86 = !DIEnumerator(name: "LZMA_MEM_ERROR", value: 5)
!87 = !DIEnumerator(name: "LZMA_MEMLIMIT_ERROR", value: 6)
!88 = !DIEnumerator(name: "LZMA_FORMAT_ERROR", value: 7)
!89 = !DIEnumerator(name: "LZMA_OPTIONS_ERROR", value: 8)
!90 = !DIEnumerator(name: "LZMA_DATA_ERROR", value: 9)
!91 = !DIEnumerator(name: "LZMA_BUF_ERROR", value: 10)
!92 = !DIEnumerator(name: "LZMA_PROG_ERROR", value: 11)
!93 = !{!94, !95}
!94 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !96, size: 64, align: 64)
!96 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !30)
!97 = !{!98, !118, !121, !126, !130, !134, !138, !141, !145, !148}
!98 = distinct !DISubprogram(name: "lzma_index_hash_init", scope: !1, file: !1, line: 73, type: !99, isLocal: false, isDefinition: true, scopeLine: 74, flags: DIFlagPrototyped, isOptimized: false, variables: !117)
!99 = !DISubroutineType(types: !100)
!100 = !{!101, !101, !104}
!101 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !102, size: 64, align: 64)
!102 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_index_hash", file: !103, line: 25, baseType: !4)
!103 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/index_hash.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!104 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !105, size: 64, align: 64)
!105 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !79, line: 403, baseType: !106)
!106 = !DICompositeType(tag: DW_TAG_structure_type, file: !79, line: 341, size: 192, align: 64, elements: !107)
!107 = !{!108, !112, !116}
!108 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !106, file: !79, line: 376, baseType: !109, size: 64, align: 64)
!109 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !110, size: 64, align: 64)
!110 = !DISubroutineType(types: !111)
!111 = !{!94, !94, !60, !60}
!112 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !106, file: !79, line: 390, baseType: !113, size: 64, align: 64, offset: 64)
!113 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !114, size: 64, align: 64)
!114 = !DISubroutineType(types: !115)
!115 = !{null, !94, !94}
!116 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !106, file: !79, line: 401, baseType: !94, size: 64, align: 64, offset: 128)
!117 = !{}
!118 = distinct !DISubprogram(name: "lzma_index_hash_end", scope: !1, file: !1, line: 104, type: !119, isLocal: false, isDefinition: true, scopeLine: 105, flags: DIFlagPrototyped, isOptimized: false, variables: !117)
!119 = !DISubroutineType(types: !120)
!120 = !{null, !101, !104}
!121 = distinct !DISubprogram(name: "lzma_index_hash_size", scope: !1, file: !1, line: 112, type: !122, isLocal: false, isDefinition: true, scopeLine: 113, flags: DIFlagPrototyped, isOptimized: false, variables: !117)
!122 = !DISubroutineType(types: !123)
!123 = !{!12, !124}
!124 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !125, size: 64, align: 64)
!125 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !102)
!126 = distinct !DISubprogram(name: "lzma_index_hash_append", scope: !1, file: !1, line: 143, type: !127, isLocal: false, isDefinition: true, scopeLine: 145, flags: DIFlagPrototyped, isOptimized: false, variables: !117)
!127 = !DISubroutineType(types: !128)
!128 = !{!129, !101, !12, !12}
!129 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !79, line: 237, baseType: !78)
!130 = distinct !DISubprogram(name: "lzma_index_hash_decode", scope: !1, file: !1, line: 174, type: !131, isLocal: false, isDefinition: true, scopeLine: 176, flags: DIFlagPrototyped, isOptimized: false, variables: !117)
!131 = !DISubroutineType(types: !132)
!132 = !{!129, !101, !95, !133, !60}
!133 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !60, size: 64, align: 64)
!134 = distinct !DISubprogram(name: "index_size", scope: !135, file: !135, line: 57, type: !136, isLocal: true, isDefinition: true, scopeLine: 58, flags: DIFlagPrototyped, isOptimized: false, variables: !117)
!135 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/index.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!136 = !DISubroutineType(types: !137)
!137 = !{!12, !12, !12}
!138 = distinct !DISubprogram(name: "vli_ceil4", scope: !135, file: !135, line: 39, type: !139, isLocal: true, isDefinition: true, scopeLine: 40, flags: DIFlagPrototyped, isOptimized: false, variables: !117)
!139 = !DISubroutineType(types: !140)
!140 = !{!12, !12}
!141 = distinct !DISubprogram(name: "hash_append", scope: !1, file: !1, line: 124, type: !142, isLocal: true, isDefinition: true, scopeLine: 126, flags: DIFlagPrototyped, isOptimized: false, variables: !117)
!142 = !DISubroutineType(types: !143)
!143 = !{!129, !144, !12, !12}
!144 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64, align: 64)
!145 = distinct !DISubprogram(name: "index_stream_size", scope: !135, file: !135, line: 65, type: !146, isLocal: true, isDefinition: true, scopeLine: 67, flags: DIFlagPrototyped, isOptimized: false, variables: !117)
!146 = !DISubroutineType(types: !147)
!147 = !{!12, !12, !12, !12}
!148 = distinct !DISubprogram(name: "index_size_unpadded", scope: !135, file: !135, line: 48, type: !136, isLocal: true, isDefinition: true, scopeLine: 49, flags: DIFlagPrototyped, isOptimized: false, variables: !117)
!149 = !{i32 2, !"Dwarf Version", i32 4}
!150 = !{i32 2, !"Debug Info Version", i32 3}
!151 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!152 = !DILocalVariable(name: "index_hash", arg: 1, scope: !98, file: !1, line: 73, type: !101)
!153 = !DIExpression()
!154 = !DILocation(line: 73, column: 39, scope: !98)
!155 = !DILocalVariable(name: "allocator", arg: 2, scope: !98, file: !1, line: 73, type: !104)
!156 = !DILocation(line: 73, column: 67, scope: !98)
!157 = !DILocation(line: 75, column: 6, scope: !158)
!158 = distinct !DILexicalBlock(scope: !98, file: !1, line: 75, column: 6)
!159 = !DILocation(line: 75, column: 17, scope: !158)
!160 = !DILocation(line: 75, column: 6, scope: !98)
!161 = !DILocation(line: 76, column: 52, scope: !162)
!162 = distinct !DILexicalBlock(scope: !158, file: !1, line: 75, column: 26)
!163 = !DILocation(line: 76, column: 16, scope: !162)
!164 = !DILocation(line: 76, column: 14, scope: !162)
!165 = !DILocation(line: 77, column: 7, scope: !166)
!166 = distinct !DILexicalBlock(scope: !162, file: !1, line: 77, column: 7)
!167 = !DILocation(line: 77, column: 18, scope: !166)
!168 = !DILocation(line: 77, column: 7, scope: !162)
!169 = !DILocation(line: 78, column: 4, scope: !166)
!170 = !DILocation(line: 79, column: 2, scope: !162)
!171 = !DILocation(line: 81, column: 2, scope: !98)
!172 = !DILocation(line: 81, column: 14, scope: !98)
!173 = !DILocation(line: 81, column: 23, scope: !98)
!174 = !DILocation(line: 82, column: 2, scope: !98)
!175 = !DILocation(line: 82, column: 14, scope: !98)
!176 = !DILocation(line: 82, column: 21, scope: !98)
!177 = !DILocation(line: 82, column: 33, scope: !98)
!178 = !DILocation(line: 83, column: 2, scope: !98)
!179 = !DILocation(line: 83, column: 14, scope: !98)
!180 = !DILocation(line: 83, column: 21, scope: !98)
!181 = !DILocation(line: 83, column: 39, scope: !98)
!182 = !DILocation(line: 84, column: 2, scope: !98)
!183 = !DILocation(line: 84, column: 14, scope: !98)
!184 = !DILocation(line: 84, column: 21, scope: !98)
!185 = !DILocation(line: 84, column: 27, scope: !98)
!186 = !DILocation(line: 85, column: 2, scope: !98)
!187 = !DILocation(line: 85, column: 14, scope: !98)
!188 = !DILocation(line: 85, column: 21, scope: !98)
!189 = !DILocation(line: 85, column: 37, scope: !98)
!190 = !DILocation(line: 86, column: 2, scope: !98)
!191 = !DILocation(line: 86, column: 14, scope: !98)
!192 = !DILocation(line: 86, column: 22, scope: !98)
!193 = !DILocation(line: 86, column: 34, scope: !98)
!194 = !DILocation(line: 87, column: 2, scope: !98)
!195 = !DILocation(line: 87, column: 14, scope: !98)
!196 = !DILocation(line: 87, column: 22, scope: !98)
!197 = !DILocation(line: 87, column: 40, scope: !98)
!198 = !DILocation(line: 88, column: 2, scope: !98)
!199 = !DILocation(line: 88, column: 14, scope: !98)
!200 = !DILocation(line: 88, column: 22, scope: !98)
!201 = !DILocation(line: 88, column: 28, scope: !98)
!202 = !DILocation(line: 89, column: 2, scope: !98)
!203 = !DILocation(line: 89, column: 14, scope: !98)
!204 = !DILocation(line: 89, column: 22, scope: !98)
!205 = !DILocation(line: 89, column: 38, scope: !98)
!206 = !DILocation(line: 90, column: 2, scope: !98)
!207 = !DILocation(line: 90, column: 14, scope: !98)
!208 = !DILocation(line: 90, column: 28, scope: !98)
!209 = !DILocation(line: 91, column: 2, scope: !98)
!210 = !DILocation(line: 91, column: 14, scope: !98)
!211 = !DILocation(line: 91, column: 32, scope: !98)
!212 = !DILocation(line: 92, column: 2, scope: !98)
!213 = !DILocation(line: 92, column: 14, scope: !98)
!214 = !DILocation(line: 92, column: 18, scope: !98)
!215 = !DILocation(line: 93, column: 2, scope: !98)
!216 = !DILocation(line: 93, column: 14, scope: !98)
!217 = !DILocation(line: 93, column: 20, scope: !98)
!218 = !DILocation(line: 96, column: 25, scope: !98)
!219 = !DILocation(line: 96, column: 37, scope: !98)
!220 = !DILocation(line: 96, column: 44, scope: !98)
!221 = !DILocation(line: 96, column: 8, scope: !98)
!222 = !DILocation(line: 97, column: 25, scope: !98)
!223 = !DILocation(line: 97, column: 37, scope: !98)
!224 = !DILocation(line: 97, column: 45, scope: !98)
!225 = !DILocation(line: 97, column: 8, scope: !98)
!226 = !DILocation(line: 99, column: 9, scope: !98)
!227 = !DILocation(line: 99, column: 2, scope: !98)
!228 = !DILocation(line: 100, column: 1, scope: !98)
!229 = !DILocalVariable(name: "index_hash", arg: 1, scope: !118, file: !1, line: 104, type: !101)
!230 = !DILocation(line: 104, column: 38, scope: !118)
!231 = !DILocalVariable(name: "allocator", arg: 2, scope: !118, file: !1, line: 104, type: !104)
!232 = !DILocation(line: 104, column: 66, scope: !118)
!233 = !DILocation(line: 106, column: 12, scope: !118)
!234 = !DILocation(line: 106, column: 24, scope: !118)
!235 = !DILocation(line: 106, column: 2, scope: !118)
!236 = !DILocation(line: 107, column: 2, scope: !118)
!237 = !DILocalVariable(name: "index_hash", arg: 1, scope: !121, file: !1, line: 112, type: !124)
!238 = !DILocation(line: 112, column: 45, scope: !121)
!239 = !DILocation(line: 117, column: 20, scope: !121)
!240 = !DILocation(line: 117, column: 32, scope: !121)
!241 = !DILocation(line: 117, column: 39, scope: !121)
!242 = !DILocation(line: 118, column: 4, scope: !121)
!243 = !DILocation(line: 118, column: 16, scope: !121)
!244 = !DILocation(line: 118, column: 23, scope: !121)
!245 = !DILocation(line: 117, column: 9, scope: !121)
!246 = !DILocation(line: 117, column: 2, scope: !121)
!247 = !DILocalVariable(name: "count", arg: 1, scope: !134, file: !135, line: 57, type: !12)
!248 = !DILocation(line: 57, column: 21, scope: !134)
!249 = !DILocalVariable(name: "index_list_size", arg: 2, scope: !134, file: !135, line: 57, type: !12)
!250 = !DILocation(line: 57, column: 37, scope: !134)
!251 = !DILocation(line: 59, column: 39, scope: !134)
!252 = !DILocation(line: 59, column: 46, scope: !134)
!253 = !DILocation(line: 59, column: 19, scope: !134)
!254 = !DILocation(line: 59, column: 9, scope: !255)
!255 = !DILexicalBlockFile(scope: !134, file: !135, discriminator: 1)
!256 = !DILocation(line: 59, column: 2, scope: !134)
!257 = !DILocalVariable(name: "index_hash", arg: 1, scope: !126, file: !1, line: 143, type: !101)
!258 = !DILocation(line: 143, column: 41, scope: !126)
!259 = !DILocalVariable(name: "unpadded_size", arg: 2, scope: !126, file: !1, line: 143, type: !12)
!260 = !DILocation(line: 143, column: 62, scope: !126)
!261 = !DILocalVariable(name: "uncompressed_size", arg: 3, scope: !126, file: !1, line: 144, type: !12)
!262 = !DILocation(line: 144, column: 12, scope: !126)
!263 = !DILocation(line: 147, column: 6, scope: !264)
!264 = distinct !DILexicalBlock(scope: !126, file: !1, line: 147, column: 6)
!265 = !DILocation(line: 147, column: 18, scope: !264)
!266 = !DILocation(line: 147, column: 27, scope: !264)
!267 = !DILocation(line: 148, column: 4, scope: !264)
!268 = !DILocation(line: 148, column: 7, scope: !269)
!269 = !DILexicalBlockFile(scope: !264, file: !1, discriminator: 1)
!270 = !DILocation(line: 148, column: 21, scope: !269)
!271 = !DILocation(line: 149, column: 4, scope: !264)
!272 = !DILocation(line: 149, column: 7, scope: !269)
!273 = !DILocation(line: 149, column: 21, scope: !269)
!274 = !DILocation(line: 150, column: 4, scope: !264)
!275 = !DILocation(line: 150, column: 7, scope: !269)
!276 = !DILocation(line: 150, column: 25, scope: !269)
!277 = !DILocation(line: 147, column: 6, scope: !278)
!278 = !DILexicalBlockFile(scope: !126, file: !1, discriminator: 1)
!279 = !DILocation(line: 151, column: 3, scope: !264)
!280 = !DILocation(line: 154, column: 2, scope: !126)
!281 = !DILocalVariable(name: "ret_", scope: !282, file: !1, line: 154, type: !283)
!282 = distinct !DILexicalBlock(scope: !126, file: !1, line: 154, column: 2)
!283 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !129)
!284 = !DILocation(line: 154, column: 2, scope: !282)
!285 = !DILocation(line: 154, column: 2, scope: !286)
!286 = !DILexicalBlockFile(scope: !282, file: !1, discriminator: 1)
!287 = !DILocation(line: 154, column: 2, scope: !288)
!288 = !DILexicalBlockFile(scope: !289, file: !1, discriminator: 2)
!289 = distinct !DILexicalBlock(scope: !282, file: !1, line: 154, column: 2)
!290 = !DILocation(line: 154, column: 2, scope: !291)
!291 = !DILexicalBlockFile(scope: !282, file: !1, discriminator: 3)
!292 = !DILocation(line: 158, column: 6, scope: !293)
!293 = distinct !DILexicalBlock(scope: !126, file: !1, line: 158, column: 6)
!294 = !DILocation(line: 158, column: 18, scope: !293)
!295 = !DILocation(line: 158, column: 25, scope: !293)
!296 = !DILocation(line: 158, column: 37, scope: !293)
!297 = !DILocation(line: 159, column: 4, scope: !293)
!298 = !DILocation(line: 159, column: 7, scope: !299)
!299 = !DILexicalBlockFile(scope: !293, file: !1, discriminator: 1)
!300 = !DILocation(line: 159, column: 19, scope: !299)
!301 = !DILocation(line: 159, column: 26, scope: !299)
!302 = !DILocation(line: 159, column: 44, scope: !299)
!303 = !DILocation(line: 160, column: 4, scope: !293)
!304 = !DILocation(line: 160, column: 18, scope: !299)
!305 = !DILocation(line: 160, column: 30, scope: !299)
!306 = !DILocation(line: 160, column: 37, scope: !299)
!307 = !DILocation(line: 161, column: 6, scope: !293)
!308 = !DILocation(line: 161, column: 18, scope: !293)
!309 = !DILocation(line: 161, column: 25, scope: !293)
!310 = !DILocation(line: 160, column: 7, scope: !299)
!311 = !DILocation(line: 162, column: 5, scope: !293)
!312 = !DILocation(line: 163, column: 4, scope: !293)
!313 = !DILocation(line: 163, column: 25, scope: !299)
!314 = !DILocation(line: 163, column: 37, scope: !299)
!315 = !DILocation(line: 163, column: 44, scope: !299)
!316 = !DILocation(line: 164, column: 6, scope: !293)
!317 = !DILocation(line: 164, column: 18, scope: !293)
!318 = !DILocation(line: 164, column: 25, scope: !293)
!319 = !DILocation(line: 165, column: 6, scope: !293)
!320 = !DILocation(line: 165, column: 18, scope: !293)
!321 = !DILocation(line: 165, column: 25, scope: !293)
!322 = !DILocation(line: 163, column: 7, scope: !299)
!323 = !DILocation(line: 166, column: 5, scope: !293)
!324 = !DILocation(line: 158, column: 6, scope: !278)
!325 = !DILocation(line: 167, column: 3, scope: !293)
!326 = !DILocation(line: 169, column: 2, scope: !126)
!327 = !DILocation(line: 170, column: 1, scope: !126)
!328 = !DILocalVariable(name: "info", arg: 1, scope: !141, file: !1, line: 124, type: !144)
!329 = !DILocation(line: 124, column: 35, scope: !141)
!330 = !DILocalVariable(name: "unpadded_size", arg: 2, scope: !141, file: !1, line: 124, type: !12)
!331 = !DILocation(line: 124, column: 50, scope: !141)
!332 = !DILocalVariable(name: "uncompressed_size", arg: 3, scope: !141, file: !1, line: 125, type: !12)
!333 = !DILocation(line: 125, column: 12, scope: !141)
!334 = !DILocalVariable(name: "sizes", scope: !141, file: !1, line: 127, type: !335)
!335 = !DICompositeType(tag: DW_TAG_array_type, baseType: !336, size: 128, align: 64, elements: !337)
!336 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !12)
!337 = !{!338}
!338 = !DISubrange(count: 2)
!339 = !DILocation(line: 127, column: 17, scope: !141)
!340 = !DILocation(line: 127, column: 28, scope: !141)
!341 = !DILocation(line: 127, column: 30, scope: !141)
!342 = !DILocation(line: 127, column: 45, scope: !141)
!343 = !DILocation(line: 129, column: 33, scope: !141)
!344 = !DILocation(line: 129, column: 23, scope: !141)
!345 = !DILocation(line: 129, column: 2, scope: !141)
!346 = !DILocation(line: 129, column: 8, scope: !141)
!347 = !DILocation(line: 129, column: 20, scope: !141)
!348 = !DILocation(line: 130, column: 29, scope: !141)
!349 = !DILocation(line: 130, column: 2, scope: !141)
!350 = !DILocation(line: 130, column: 8, scope: !141)
!351 = !DILocation(line: 130, column: 26, scope: !141)
!352 = !DILocation(line: 131, column: 41, scope: !141)
!353 = !DILocation(line: 131, column: 27, scope: !141)
!354 = !DILocation(line: 132, column: 20, scope: !141)
!355 = !DILocation(line: 132, column: 6, scope: !141)
!356 = !DILocation(line: 132, column: 4, scope: !141)
!357 = !DILocation(line: 131, column: 2, scope: !141)
!358 = !DILocation(line: 131, column: 8, scope: !141)
!359 = !DILocation(line: 131, column: 24, scope: !141)
!360 = !DILocation(line: 133, column: 4, scope: !141)
!361 = !DILocation(line: 133, column: 10, scope: !141)
!362 = !DILocation(line: 133, column: 2, scope: !141)
!363 = !DILocation(line: 135, column: 21, scope: !141)
!364 = !DILocation(line: 135, column: 27, scope: !141)
!365 = !DILocation(line: 136, column: 21, scope: !141)
!366 = !DILocation(line: 136, column: 4, scope: !141)
!367 = !DILocation(line: 135, column: 2, scope: !141)
!368 = !DILocation(line: 138, column: 2, scope: !141)
!369 = !DILocalVariable(name: "blocks_size", arg: 1, scope: !145, file: !135, line: 65, type: !12)
!370 = !DILocation(line: 65, column: 28, scope: !145)
!371 = !DILocalVariable(name: "count", arg: 2, scope: !145, file: !135, line: 66, type: !12)
!372 = !DILocation(line: 66, column: 12, scope: !145)
!373 = !DILocalVariable(name: "index_list_size", arg: 3, scope: !145, file: !135, line: 66, type: !12)
!374 = !DILocation(line: 66, column: 28, scope: !145)
!375 = !DILocation(line: 68, column: 35, scope: !145)
!376 = !DILocation(line: 68, column: 33, scope: !145)
!377 = !DILocation(line: 69, column: 17, scope: !145)
!378 = !DILocation(line: 69, column: 24, scope: !145)
!379 = !DILocation(line: 69, column: 6, scope: !145)
!380 = !DILocation(line: 69, column: 4, scope: !145)
!381 = !DILocation(line: 70, column: 4, scope: !145)
!382 = !DILocation(line: 68, column: 2, scope: !145)
!383 = !DILocalVariable(name: "index_hash", arg: 1, scope: !130, file: !1, line: 174, type: !101)
!384 = !DILocation(line: 174, column: 41, scope: !130)
!385 = !DILocalVariable(name: "in", arg: 2, scope: !130, file: !1, line: 174, type: !95)
!386 = !DILocation(line: 174, column: 68, scope: !130)
!387 = !DILocalVariable(name: "in_pos", arg: 3, scope: !130, file: !1, line: 175, type: !133)
!388 = !DILocation(line: 175, column: 11, scope: !130)
!389 = !DILocalVariable(name: "in_size", arg: 4, scope: !130, file: !1, line: 175, type: !60)
!390 = !DILocation(line: 175, column: 26, scope: !130)
!391 = !DILocalVariable(name: "in_start", scope: !130, file: !1, line: 177, type: !60)
!392 = !DILocation(line: 177, column: 9, scope: !130)
!393 = !DILocalVariable(name: "ret", scope: !130, file: !1, line: 178, type: !129)
!394 = !DILocation(line: 178, column: 11, scope: !130)
!395 = !DILocation(line: 183, column: 7, scope: !396)
!396 = distinct !DILexicalBlock(scope: !130, file: !1, line: 183, column: 6)
!397 = !DILocation(line: 183, column: 6, scope: !396)
!398 = !DILocation(line: 183, column: 17, scope: !396)
!399 = !DILocation(line: 183, column: 14, scope: !396)
!400 = !DILocation(line: 183, column: 6, scope: !130)
!401 = !DILocation(line: 184, column: 3, scope: !396)
!402 = !DILocation(line: 189, column: 14, scope: !130)
!403 = !DILocation(line: 189, column: 13, scope: !130)
!404 = !DILocation(line: 189, column: 11, scope: !130)
!405 = !DILocation(line: 190, column: 6, scope: !130)
!406 = !DILocation(line: 192, column: 2, scope: !130)
!407 = !DILocation(line: 192, column: 10, scope: !408)
!408 = !DILexicalBlockFile(scope: !130, file: !1, discriminator: 1)
!409 = !DILocation(line: 192, column: 9, scope: !408)
!410 = !DILocation(line: 192, column: 19, scope: !408)
!411 = !DILocation(line: 192, column: 17, scope: !408)
!412 = !DILocation(line: 192, column: 2, scope: !408)
!413 = !DILocation(line: 193, column: 10, scope: !130)
!414 = !DILocation(line: 193, column: 22, scope: !130)
!415 = !DILocation(line: 193, column: 2, scope: !130)
!416 = !DILocation(line: 196, column: 12, scope: !417)
!417 = distinct !DILexicalBlock(scope: !418, file: !1, line: 196, column: 7)
!418 = distinct !DILexicalBlock(scope: !130, file: !1, line: 193, column: 32)
!419 = !DILocation(line: 196, column: 19, scope: !417)
!420 = !DILocation(line: 196, column: 7, scope: !417)
!421 = !DILocation(line: 196, column: 23, scope: !417)
!422 = !DILocation(line: 196, column: 7, scope: !418)
!423 = !DILocation(line: 197, column: 4, scope: !417)
!424 = !DILocation(line: 199, column: 3, scope: !418)
!425 = !DILocation(line: 199, column: 15, scope: !418)
!426 = !DILocation(line: 199, column: 24, scope: !418)
!427 = !DILocation(line: 200, column: 3, scope: !418)
!428 = !DILocation(line: 203, column: 26, scope: !429)
!429 = distinct !DILexicalBlock(scope: !418, file: !1, line: 202, column: 18)
!430 = !DILocation(line: 203, column: 38, scope: !429)
!431 = !DILocation(line: 204, column: 6, scope: !429)
!432 = !DILocation(line: 204, column: 18, scope: !429)
!433 = !DILocation(line: 204, column: 23, scope: !429)
!434 = !DILocation(line: 204, column: 27, scope: !429)
!435 = !DILocation(line: 204, column: 35, scope: !429)
!436 = !DILocation(line: 203, column: 9, scope: !429)
!437 = !DILocation(line: 203, column: 7, scope: !429)
!438 = !DILocation(line: 205, column: 7, scope: !439)
!439 = distinct !DILexicalBlock(scope: !429, file: !1, line: 205, column: 7)
!440 = !DILocation(line: 205, column: 11, scope: !439)
!441 = !DILocation(line: 205, column: 7, scope: !429)
!442 = !DILocation(line: 206, column: 4, scope: !439)
!443 = !DILocation(line: 209, column: 7, scope: !444)
!444 = distinct !DILexicalBlock(scope: !429, file: !1, line: 209, column: 7)
!445 = !DILocation(line: 209, column: 19, scope: !444)
!446 = !DILocation(line: 209, column: 32, scope: !444)
!447 = !DILocation(line: 209, column: 44, scope: !444)
!448 = !DILocation(line: 209, column: 51, scope: !444)
!449 = !DILocation(line: 209, column: 29, scope: !444)
!450 = !DILocation(line: 209, column: 7, scope: !429)
!451 = !DILocation(line: 210, column: 4, scope: !444)
!452 = !DILocation(line: 212, column: 7, scope: !429)
!453 = !DILocation(line: 213, column: 3, scope: !429)
!454 = !DILocation(line: 213, column: 15, scope: !429)
!455 = !DILocation(line: 213, column: 19, scope: !429)
!456 = !DILocation(line: 216, column: 26, scope: !429)
!457 = !DILocation(line: 216, column: 38, scope: !429)
!458 = !DILocation(line: 216, column: 48, scope: !429)
!459 = !DILocation(line: 216, column: 3, scope: !429)
!460 = !DILocation(line: 216, column: 15, scope: !429)
!461 = !DILocation(line: 216, column: 24, scope: !429)
!462 = !DILocation(line: 218, column: 3, scope: !429)
!463 = !DILocalVariable(name: "size", scope: !464, file: !1, line: 223, type: !465)
!464 = distinct !DILexicalBlock(scope: !418, file: !1, line: 222, column: 25)
!465 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !12, size: 64, align: 64)
!466 = !DILocation(line: 223, column: 13, scope: !464)
!467 = !DILocation(line: 223, column: 20, scope: !464)
!468 = !DILocation(line: 223, column: 32, scope: !464)
!469 = !DILocation(line: 223, column: 41, scope: !464)
!470 = !DILocation(line: 224, column: 8, scope: !464)
!471 = !DILocation(line: 224, column: 20, scope: !464)
!472 = !DILocation(line: 223, column: 20, scope: !473)
!473 = !DILexicalBlockFile(scope: !464, file: !1, discriminator: 1)
!474 = !DILocation(line: 225, column: 8, scope: !464)
!475 = !DILocation(line: 225, column: 20, scope: !464)
!476 = !DILocation(line: 223, column: 20, scope: !477)
!477 = !DILexicalBlockFile(scope: !464, file: !1, discriminator: 2)
!478 = !DILocation(line: 223, column: 20, scope: !479)
!479 = !DILexicalBlockFile(scope: !464, file: !1, discriminator: 3)
!480 = !DILocation(line: 223, column: 13, scope: !479)
!481 = !DILocation(line: 227, column: 25, scope: !464)
!482 = !DILocation(line: 227, column: 32, scope: !464)
!483 = !DILocation(line: 227, column: 44, scope: !464)
!484 = !DILocation(line: 228, column: 5, scope: !464)
!485 = !DILocation(line: 228, column: 9, scope: !464)
!486 = !DILocation(line: 228, column: 17, scope: !464)
!487 = !DILocation(line: 227, column: 9, scope: !464)
!488 = !DILocation(line: 227, column: 7, scope: !464)
!489 = !DILocation(line: 229, column: 7, scope: !490)
!490 = distinct !DILexicalBlock(scope: !464, file: !1, line: 229, column: 7)
!491 = !DILocation(line: 229, column: 11, scope: !490)
!492 = !DILocation(line: 229, column: 7, scope: !464)
!493 = !DILocation(line: 230, column: 4, scope: !490)
!494 = !DILocation(line: 232, column: 7, scope: !464)
!495 = !DILocation(line: 233, column: 3, scope: !464)
!496 = !DILocation(line: 233, column: 15, scope: !464)
!497 = !DILocation(line: 233, column: 19, scope: !464)
!498 = !DILocation(line: 235, column: 7, scope: !499)
!499 = distinct !DILexicalBlock(scope: !464, file: !1, line: 235, column: 7)
!500 = !DILocation(line: 235, column: 19, scope: !499)
!501 = !DILocation(line: 235, column: 28, scope: !499)
!502 = !DILocation(line: 235, column: 7, scope: !464)
!503 = !DILocation(line: 236, column: 8, scope: !504)
!504 = distinct !DILexicalBlock(scope: !505, file: !1, line: 236, column: 8)
!505 = distinct !DILexicalBlock(scope: !499, file: !1, line: 235, column: 45)
!506 = !DILocation(line: 236, column: 20, scope: !504)
!507 = !DILocation(line: 236, column: 34, scope: !504)
!508 = !DILocation(line: 237, column: 6, scope: !504)
!509 = !DILocation(line: 237, column: 9, scope: !510)
!510 = !DILexicalBlockFile(scope: !504, file: !1, discriminator: 1)
!511 = !DILocation(line: 237, column: 21, scope: !510)
!512 = !DILocation(line: 238, column: 7, scope: !504)
!513 = !DILocation(line: 236, column: 8, scope: !514)
!514 = !DILexicalBlockFile(scope: !505, file: !1, discriminator: 1)
!515 = !DILocation(line: 239, column: 5, scope: !504)
!516 = !DILocation(line: 241, column: 4, scope: !505)
!517 = !DILocation(line: 241, column: 16, scope: !505)
!518 = !DILocation(line: 241, column: 25, scope: !505)
!519 = !DILocation(line: 242, column: 3, scope: !505)
!520 = !DILocation(line: 244, column: 4, scope: !521)
!521 = distinct !DILexicalBlock(scope: !499, file: !1, line: 242, column: 10)
!522 = !DILocalVariable(name: "ret_", scope: !523, file: !1, line: 244, type: !283)
!523 = distinct !DILexicalBlock(scope: !521, file: !1, line: 244, column: 4)
!524 = !DILocation(line: 244, column: 4, scope: !523)
!525 = !DILocation(line: 244, column: 4, scope: !526)
!526 = !DILexicalBlockFile(scope: !523, file: !1, discriminator: 1)
!527 = !DILocation(line: 244, column: 4, scope: !528)
!528 = !DILexicalBlockFile(scope: !529, file: !1, discriminator: 2)
!529 = distinct !DILexicalBlock(scope: !523, file: !1, line: 244, column: 4)
!530 = !DILocation(line: 244, column: 4, scope: !531)
!531 = !DILexicalBlockFile(scope: !523, file: !1, discriminator: 3)
!532 = !DILocation(line: 254, column: 8, scope: !533)
!533 = distinct !DILexicalBlock(scope: !521, file: !1, line: 254, column: 8)
!534 = !DILocation(line: 254, column: 20, scope: !533)
!535 = !DILocation(line: 254, column: 27, scope: !533)
!536 = !DILocation(line: 255, column: 8, scope: !533)
!537 = !DILocation(line: 255, column: 20, scope: !533)
!538 = !DILocation(line: 255, column: 28, scope: !533)
!539 = !DILocation(line: 255, column: 6, scope: !533)
!540 = !DILocation(line: 256, column: 6, scope: !533)
!541 = !DILocation(line: 256, column: 9, scope: !542)
!542 = !DILexicalBlockFile(scope: !533, file: !1, discriminator: 1)
!543 = !DILocation(line: 256, column: 21, scope: !542)
!544 = !DILocation(line: 256, column: 28, scope: !542)
!545 = !DILocation(line: 257, column: 8, scope: !533)
!546 = !DILocation(line: 257, column: 20, scope: !533)
!547 = !DILocation(line: 257, column: 28, scope: !533)
!548 = !DILocation(line: 257, column: 6, scope: !533)
!549 = !DILocation(line: 258, column: 6, scope: !533)
!550 = !DILocation(line: 258, column: 9, scope: !542)
!551 = !DILocation(line: 258, column: 21, scope: !542)
!552 = !DILocation(line: 258, column: 28, scope: !542)
!553 = !DILocation(line: 259, column: 8, scope: !533)
!554 = !DILocation(line: 259, column: 20, scope: !533)
!555 = !DILocation(line: 259, column: 28, scope: !533)
!556 = !DILocation(line: 259, column: 6, scope: !533)
!557 = !DILocation(line: 254, column: 8, scope: !558)
!558 = !DILexicalBlockFile(scope: !521, file: !1, discriminator: 1)
!559 = !DILocation(line: 260, column: 5, scope: !533)
!560 = !DILocation(line: 263, column: 29, scope: !521)
!561 = !DILocation(line: 263, column: 41, scope: !521)
!562 = !DILocation(line: 263, column: 27, scope: !521)
!563 = !DILocation(line: 263, column: 51, scope: !521)
!564 = !DILocation(line: 263, column: 4, scope: !521)
!565 = !DILocation(line: 263, column: 16, scope: !521)
!566 = !DILocation(line: 263, column: 25, scope: !521)
!567 = !DILocation(line: 267, column: 3, scope: !464)
!568 = !DILocation(line: 272, column: 5, scope: !418)
!569 = !DILocation(line: 272, column: 17, scope: !418)
!570 = !DILocation(line: 272, column: 25, scope: !418)
!571 = !DILocation(line: 273, column: 5, scope: !418)
!572 = !DILocation(line: 273, column: 17, scope: !418)
!573 = !DILocation(line: 273, column: 25, scope: !418)
!574 = !DILocation(line: 271, column: 38, scope: !418)
!575 = !DILocation(line: 271, column: 36, scope: !418)
!576 = !DILocation(line: 273, column: 43, scope: !418)
!577 = !DILocation(line: 271, column: 3, scope: !418)
!578 = !DILocation(line: 271, column: 15, scope: !418)
!579 = !DILocation(line: 271, column: 19, scope: !418)
!580 = !DILocation(line: 274, column: 3, scope: !418)
!581 = !DILocation(line: 274, column: 15, scope: !418)
!582 = !DILocation(line: 274, column: 24, scope: !418)
!583 = !DILocation(line: 279, column: 7, scope: !584)
!584 = distinct !DILexicalBlock(scope: !418, file: !1, line: 279, column: 7)
!585 = !DILocation(line: 279, column: 19, scope: !584)
!586 = !DILocation(line: 279, column: 23, scope: !584)
!587 = !DILocation(line: 279, column: 7, scope: !418)
!588 = !DILocation(line: 280, column: 6, scope: !589)
!589 = distinct !DILexicalBlock(scope: !584, file: !1, line: 279, column: 28)
!590 = !DILocation(line: 280, column: 18, scope: !589)
!591 = !DILocation(line: 280, column: 4, scope: !589)
!592 = !DILocation(line: 281, column: 13, scope: !593)
!593 = distinct !DILexicalBlock(scope: !589, file: !1, line: 281, column: 8)
!594 = !DILocation(line: 281, column: 20, scope: !593)
!595 = !DILocation(line: 281, column: 8, scope: !593)
!596 = !DILocation(line: 281, column: 24, scope: !593)
!597 = !DILocation(line: 281, column: 8, scope: !589)
!598 = !DILocation(line: 282, column: 5, scope: !593)
!599 = !DILocation(line: 284, column: 4, scope: !589)
!600 = !DILocation(line: 288, column: 7, scope: !601)
!601 = distinct !DILexicalBlock(scope: !418, file: !1, line: 288, column: 7)
!602 = !DILocation(line: 288, column: 19, scope: !601)
!603 = !DILocation(line: 288, column: 26, scope: !601)
!604 = !DILocation(line: 289, column: 8, scope: !601)
!605 = !DILocation(line: 289, column: 20, scope: !601)
!606 = !DILocation(line: 289, column: 28, scope: !601)
!607 = !DILocation(line: 289, column: 5, scope: !601)
!608 = !DILocation(line: 290, column: 5, scope: !601)
!609 = !DILocation(line: 290, column: 8, scope: !610)
!610 = !DILexicalBlockFile(scope: !601, file: !1, discriminator: 1)
!611 = !DILocation(line: 290, column: 20, scope: !610)
!612 = !DILocation(line: 290, column: 27, scope: !610)
!613 = !DILocation(line: 291, column: 8, scope: !601)
!614 = !DILocation(line: 291, column: 20, scope: !601)
!615 = !DILocation(line: 291, column: 28, scope: !601)
!616 = !DILocation(line: 291, column: 5, scope: !601)
!617 = !DILocation(line: 292, column: 5, scope: !601)
!618 = !DILocation(line: 292, column: 8, scope: !610)
!619 = !DILocation(line: 292, column: 20, scope: !610)
!620 = !DILocation(line: 292, column: 27, scope: !610)
!621 = !DILocation(line: 293, column: 8, scope: !601)
!622 = !DILocation(line: 293, column: 20, scope: !601)
!623 = !DILocation(line: 293, column: 28, scope: !601)
!624 = !DILocation(line: 293, column: 5, scope: !601)
!625 = !DILocation(line: 288, column: 7, scope: !626)
!626 = !DILexicalBlockFile(scope: !418, file: !1, discriminator: 1)
!627 = !DILocation(line: 294, column: 4, scope: !601)
!628 = !DILocation(line: 297, column: 22, scope: !418)
!629 = !DILocation(line: 297, column: 34, scope: !418)
!630 = !DILocation(line: 297, column: 41, scope: !418)
!631 = !DILocation(line: 297, column: 3, scope: !418)
!632 = !DILocation(line: 298, column: 22, scope: !418)
!633 = !DILocation(line: 298, column: 34, scope: !418)
!634 = !DILocation(line: 298, column: 42, scope: !418)
!635 = !DILocation(line: 298, column: 3, scope: !418)
!636 = !DILocation(line: 299, column: 14, scope: !637)
!637 = distinct !DILexicalBlock(scope: !418, file: !1, line: 299, column: 7)
!638 = !DILocation(line: 299, column: 26, scope: !637)
!639 = !DILocation(line: 299, column: 33, scope: !637)
!640 = !DILocation(line: 299, column: 39, scope: !637)
!641 = !DILocation(line: 299, column: 46, scope: !637)
!642 = !DILocation(line: 300, column: 5, scope: !637)
!643 = !DILocation(line: 300, column: 17, scope: !637)
!644 = !DILocation(line: 300, column: 25, scope: !637)
!645 = !DILocation(line: 300, column: 31, scope: !637)
!646 = !DILocation(line: 300, column: 38, scope: !637)
!647 = !DILocation(line: 301, column: 5, scope: !637)
!648 = !DILocation(line: 299, column: 7, scope: !637)
!649 = !DILocation(line: 301, column: 39, scope: !637)
!650 = !DILocation(line: 299, column: 7, scope: !418)
!651 = !DILocation(line: 302, column: 4, scope: !637)
!652 = !DILocation(line: 305, column: 34, scope: !418)
!653 = !DILocation(line: 305, column: 39, scope: !418)
!654 = !DILocation(line: 305, column: 37, scope: !418)
!655 = !DILocation(line: 306, column: 6, scope: !418)
!656 = !DILocation(line: 306, column: 5, scope: !418)
!657 = !DILocation(line: 306, column: 15, scope: !418)
!658 = !DILocation(line: 306, column: 13, scope: !418)
!659 = !DILocation(line: 306, column: 25, scope: !418)
!660 = !DILocation(line: 306, column: 37, scope: !418)
!661 = !DILocation(line: 305, column: 23, scope: !418)
!662 = !DILocation(line: 305, column: 3, scope: !418)
!663 = !DILocation(line: 305, column: 15, scope: !418)
!664 = !DILocation(line: 305, column: 21, scope: !418)
!665 = !DILocation(line: 308, column: 3, scope: !418)
!666 = !DILocation(line: 308, column: 15, scope: !418)
!667 = !DILocation(line: 308, column: 24, scope: !418)
!668 = !DILocation(line: 313, column: 3, scope: !418)
!669 = !DILocation(line: 314, column: 9, scope: !670)
!670 = distinct !DILexicalBlock(scope: !671, file: !1, line: 314, column: 8)
!671 = distinct !DILexicalBlock(scope: !418, file: !1, line: 313, column: 6)
!672 = !DILocation(line: 314, column: 8, scope: !670)
!673 = !DILocation(line: 314, column: 19, scope: !670)
!674 = !DILocation(line: 314, column: 16, scope: !670)
!675 = !DILocation(line: 314, column: 8, scope: !671)
!676 = !DILocation(line: 315, column: 5, scope: !670)
!677 = !DILocation(line: 317, column: 10, scope: !678)
!678 = distinct !DILexicalBlock(scope: !671, file: !1, line: 317, column: 8)
!679 = !DILocation(line: 317, column: 22, scope: !678)
!680 = !DILocation(line: 317, column: 32, scope: !678)
!681 = !DILocation(line: 317, column: 44, scope: !678)
!682 = !DILocation(line: 317, column: 48, scope: !678)
!683 = !DILocation(line: 317, column: 28, scope: !678)
!684 = !DILocation(line: 318, column: 6, scope: !678)
!685 = !DILocation(line: 318, column: 22, scope: !678)
!686 = !DILocation(line: 318, column: 29, scope: !678)
!687 = !DILocation(line: 318, column: 17, scope: !678)
!688 = !DILocation(line: 318, column: 14, scope: !678)
!689 = !DILocation(line: 317, column: 8, scope: !671)
!690 = !DILocation(line: 319, column: 5, scope: !678)
!691 = !DILocation(line: 321, column: 3, scope: !671)
!692 = !DILocation(line: 321, column: 14, scope: !626)
!693 = !DILocation(line: 321, column: 26, scope: !626)
!694 = !DILocation(line: 321, column: 12, scope: !626)
!695 = !DILocation(line: 321, column: 30, scope: !626)
!696 = !DILocation(line: 321, column: 3, scope: !626)
!697 = !DILocation(line: 323, column: 3, scope: !418)
!698 = !DILocation(line: 326, column: 3, scope: !418)
!699 = !DILocation(line: 192, column: 2, scope: !700)
!700 = !DILexicalBlockFile(scope: !130, file: !1, discriminator: 2)
!701 = !DILocation(line: 192, column: 2, scope: !702)
!702 = !DILexicalBlockFile(scope: !130, file: !1, discriminator: 3)
!703 = !DILocation(line: 332, column: 33, scope: !130)
!704 = !DILocation(line: 332, column: 38, scope: !130)
!705 = !DILocation(line: 332, column: 36, scope: !130)
!706 = !DILocation(line: 333, column: 5, scope: !130)
!707 = !DILocation(line: 333, column: 4, scope: !130)
!708 = !DILocation(line: 333, column: 14, scope: !130)
!709 = !DILocation(line: 333, column: 12, scope: !130)
!710 = !DILocation(line: 333, column: 24, scope: !130)
!711 = !DILocation(line: 333, column: 36, scope: !130)
!712 = !DILocation(line: 332, column: 22, scope: !130)
!713 = !DILocation(line: 332, column: 2, scope: !130)
!714 = !DILocation(line: 332, column: 14, scope: !130)
!715 = !DILocation(line: 332, column: 20, scope: !130)
!716 = !DILocation(line: 335, column: 9, scope: !130)
!717 = !DILocation(line: 335, column: 2, scope: !130)
!718 = !DILocation(line: 336, column: 1, scope: !130)
!719 = !DILocalVariable(name: "count", arg: 1, scope: !148, file: !135, line: 48, type: !12)
!720 = !DILocation(line: 48, column: 30, scope: !148)
!721 = !DILocalVariable(name: "index_list_size", arg: 2, scope: !148, file: !135, line: 48, type: !12)
!722 = !DILocation(line: 48, column: 46, scope: !148)
!723 = !DILocation(line: 51, column: 27, scope: !148)
!724 = !DILocation(line: 51, column: 13, scope: !148)
!725 = !DILocation(line: 51, column: 11, scope: !148)
!726 = !DILocation(line: 51, column: 9, scope: !148)
!727 = !DILocation(line: 51, column: 36, scope: !148)
!728 = !DILocation(line: 51, column: 34, scope: !148)
!729 = !DILocation(line: 51, column: 52, scope: !148)
!730 = !DILocation(line: 51, column: 2, scope: !148)
!731 = !DILocalVariable(name: "vli", arg: 1, scope: !138, file: !135, line: 39, type: !12)
!732 = !DILocation(line: 39, column: 20, scope: !138)
!733 = !DILocation(line: 41, column: 2, scope: !138)
!734 = !DILocation(line: 41, column: 2, scope: !735)
!735 = !DILexicalBlockFile(scope: !138, file: !135, discriminator: 1)
!736 = !DILocation(line: 41, column: 2, scope: !737)
!737 = !DILexicalBlockFile(scope: !138, file: !135, discriminator: 2)
!738 = !DILocation(line: 41, column: 2, scope: !739)
!739 = !DILexicalBlockFile(scope: !138, file: !135, discriminator: 3)
!740 = !DILocation(line: 42, column: 10, scope: !138)
!741 = !DILocation(line: 42, column: 14, scope: !138)
!742 = !DILocation(line: 42, column: 19, scope: !138)
!743 = !DILocation(line: 42, column: 2, scope: !138)
